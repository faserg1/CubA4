#include "./RenderChunkCompilerCore.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/DebugMarker.hpp"
#include <world/IChunk.hpp>
#include <object/IBlock.hpp>
#include "../memory/MemoryManager.hpp"
#include "../model/ModelCompiler.hpp"
#include <algorithm>
#include <numeric> 
#include <tuple> 
#include <execution>
#include <string>
#include <cmath>
#include <unordered_map>
#include <fmt/format.h>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::util;
using namespace CubA4::model;
using namespace CubA4::world;

constexpr const unsigned short commandPoolsCount = 64;

RenderChunkCompilerCore::RenderChunkCompilerCore(std::shared_ptr<const ICore> core, std::shared_ptr<const Device> device, std::shared_ptr<CubA4::render::engine::model::ModelManager> modelManager) :
	core_(core), device_(device), memManager_(std::make_shared<MemoryManager>(device)), modelManager_(modelManager)
{
	initCommandPools();
	initDescriptorPools();
}

RenderChunkCompilerCore::~RenderChunkCompilerCore()
{
}

std::unique_ptr<const CommandPool::CommandPoolLock> RenderChunkCompilerCore::lockCommandPool()
{
	while (true)
	{
		std::unique_ptr<const CommandPool::CommandPoolLock> lock;
		for (auto pool : commandPools_)
		{
			lock = pool->tryLock();
			if (lock)
				break;
		}

		if (!lock)
			continue;
		return std::move(lock);
	}
}

sVkDescriptorPool RenderChunkCompilerCore::getDescriptorPool(const std::unique_ptr<const CommandPool::CommandPoolLock> &lock)
{
	auto pool = lock->getPool();
	auto it = std::find_if(commandPools_.begin(), commandPools_.end(), [pool](std::shared_ptr<CommandPool> checkingPool) -> bool
	{
		return pool == checkingPool;
	});
	if (it == commandPools_.end())
	{
		//TODO: [OOKAMI] exceptions, etc
		return {};
	}
	auto index = std::distance(commandPools_.begin(), it);
	return descriptorPools_[index];
}

void RenderChunkCompilerCore::initCommandPools()
{
	commandPools_.reserve(commandPoolsCount);
	for (unsigned short i = 0; i < commandPoolsCount; i++)
		commandPools_.push_back(std::make_shared<CommandPool>(device_, 0));
}

void RenderChunkCompilerCore::initDescriptorPools()
{
	VkDescriptorPool pool = {};
	VkDescriptorPoolCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	createInfo.maxSets = 16;
	createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	
	std::vector<VkDescriptorPoolSize> sizes;

	sizes.push_back({ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 16});

	createInfo.pPoolSizes = sizes.data();
	createInfo.poolSizeCount = static_cast<uint32_t>(sizes.size());


	for (unsigned short i = 0; i < commandPoolsCount; i++)
	{
		vkCreateDescriptorPool(device_->getDevice(), &createInfo, nullptr, &pool);
		std::function<void(VkDescriptorPool)> deleter = [dev = device_](VkDescriptorPool pool)
		{
			vkDestroyDescriptorPool(dev->getDevice(), pool, nullptr);
		};
		descriptorPools_.push_back(createSharedVulkanObject(pool, deleter));
	}
}

RenderChunkCompilerCore::RenderModels RenderChunkCompilerCore::compileBlocks(std::shared_ptr<const CubA4::world::IChunk> chunk)
{
	RenderModels models;
	auto cpos = chunk->getChunkPos();
	auto visibleFaces = compileVisibleSides(chunk);
	struct Def
	{
		std::vector<BlockPtr> blocks;
		std::string materialId;
	};
	using Key = std::shared_ptr<const CubA4::render::engine::material::IMaterial>;
	std::unordered_map<Key, Def> materialsToDefMap;

	auto usedBlocks = chunk->getUsedBlocks();
	auto env = core_->getEnvironment();

	for (auto blockId : usedBlocks)
	{
		auto block = env->getObjectT<CubA4::object::IBlock>(blockId);
		auto modelDef = block->getRenderModelDefinition();
		auto usedMaterials = modelDef->getUsedMaterials();
		for (const auto &materialId : usedMaterials)
		{
			auto material = modelDef->getMaterial(materialId);
			if (auto it = materialsToDefMap.find(material); it != materialsToDefMap.end())
			{
				it->second.blocks.push_back(block);
			}
			else
			{
				auto blocks = std::vector{block};
				auto def = Def {
					.blocks = blocks,
					.materialId = materialId
				};
				materialsToDefMap.insert(std::make_pair(material, def));
			}
		}
	}

	for (const auto &pair : materialsToDefMap)
	{
		auto compiledModel = compileModelByMaterial(chunk, pair.second.materialId, pair.second.blocks, visibleFaces);
		if (!compiledModel)
			continue;
		auto material = std::dynamic_pointer_cast<const CubA4::render::engine::material::Material>(pair.first);
		models.insert(std::make_pair(material, compiledModel));
	}

	return std::move(models);
}

RenderChunkCompilerCore::RenderModelPtr RenderChunkCompilerCore::compileModelByMaterial(std::shared_ptr<const CubA4::world::IChunk> chunk, const std::string &material, std::vector<BlockPtr> blocks, const VisibleSides &visibleFaces)
{
	auto cpos = chunk->getChunkPos();
	auto start = clock();
	auto cl = start;
	model::ModelCompiler compiler;
	auto env = core_->getEnvironment();
	
	for (auto block : blocks)
	{
		auto blockId = env->getId(block);
		auto blockDataContainer = chunk->getDataProvider().getBlockDataStorage(blockId);
		auto model = block->getRenderModelDefinition();
		const auto usedMaterials = model->getUsedMaterials();
		if (std::find(usedMaterials.begin(), usedMaterials.end(), material) == usedMaterials.end())
			continue;
		auto containers = chunk->getChunkBContainers(blockId);
		std::vector<model::ModelCompiler::CollectedData> collectedData;
		using TupleKey = std::tuple<std::string, BlockSides, uint64_t>;
		using FacesValues = decltype(model::ModelCompiler::CollectedData::faces);
		std::map<TupleKey, FacesValues> facesCache;
		collectedData.reserve(containers.size());
		for (auto &container : containers)
		{
			for (auto [index, side] : visibleFaces)
			{
				if (!container->hasBlockAt(index))
					continue;
				const auto dataId = container->getBlockData(index);
				const auto hiddenSides = ~side & AllSides;
				FacesValues faces;
				auto key = std::make_tuple(material, hiddenSides, dataId);
				if (auto it = facesCache.find(key); it != facesCache.end())
				{
					faces = it->second;
				}
				else
				{
					const auto data = blockDataContainer->get(dataId);
					faces = std::make_shared<std::vector<unsigned short>>(model->getFaces(material, hiddenSides, *data));
					facesCache.insert(std::make_pair(key, faces));
				}
				
				model::ModelCompiler::CollectedData cdata;
				cdata.model = model.get(),
				cdata.faces = faces,
				cdata.pos = container->getBlockPosition(index);
				collectedData.push_back(cdata);
			}
		}
		compiler.addFaces(std::move(collectedData));
	}

	
	//core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Model collecting {}, {}, {} done in {} ticks", cpos.x, cpos.y, cpos.z, clock() - cl));
	cl = clock();
	auto model = compiler.compile(material, modelManager_);
	//core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Model building {}, {}, {} done in {} ticks", cpos.x, cpos.y, cpos.z, clock() - cl));
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Model building total {}, {}, {} done in {} ticks", cpos.x, cpos.y, cpos.z, clock() - start));
	return model;
}

RenderChunkCompilerCore::HiddenSides RenderChunkCompilerCore::compileHiddenSides(std::shared_ptr<const IChunk> chunk) const
{
	RenderChunkCompilerCore::HiddenSides hiddenSides;
	hiddenSides.fill(0);
	auto env = core_->getEnvironment();
	for (auto container : chunk->getChunkBContainers())
	{
		auto blockId = container->getBlockId();
		auto block = env->getObjectT<CubA4::object::IBlock>(blockId);
		auto blockDataContainer = chunk->getDataProvider().getBlockDataStorage(blockId);
		std::for_each(std::execution::par_unseq, container->begin(), container->end(), [this, &container, &block, &hiddenSides, blockDataContainer](auto blockPos)
		{
			if (!container->hasBlockAt(blockPos))
				return;
			const auto dataId = container->getBlockData(blockPos);
			const auto data = blockDataContainer->get(dataId);
			auto nonOpaque = block->getRenderModelDefinition()->getNonOpaqueSide(*data);
			hideFrom(hiddenSides, blockPos, nonOpaque);
		});
	}
	return std::move(hiddenSides);
}

RenderChunkCompilerCore::VisibleSides RenderChunkCompilerCore::compileVisibleSides(std::shared_ptr<const CubA4::world::IChunk> chunk) const
{
	auto hidden = compileHiddenSides(chunk);
	VisibleSides visible;
	for (uint32_t index = 0; index < ChunkCube; index++)
	{
		if (!chunk->hasBlocksAt(index))
			continue;
		if (hidden[index] == AllSides)
			continue;	
		auto side = ~hidden[index] & AllSides;
		if (!side)
			continue;
		visible.push_back(std::make_pair(index, side));	
	}
	
	return std::move(visible);
}

void RenderChunkCompilerCore::hideFrom(HiddenSides &hiddenSides, BlockInChunkPos pos, BlockSides nonOpaque) const
{
	if (pos.x > 0 && nonOpaque & BlockSide::Left)
	{
		auto posLeft = pos;
		posLeft.x--;
		auto index = indexByPos(posLeft);
		hiddenSides[index] |= BlockSide::Right;
	}
	if (pos.x < ChunkSize - 1 && nonOpaque & BlockSide::Right)
	{
		auto posRight = pos;
		posRight.x++;
		auto index = indexByPos(posRight);
		hiddenSides[index] |= BlockSide::Left;
	}
	if (pos.y > 0 && nonOpaque & BlockSide::Bottom)
	{
		auto posBottom = pos;
		posBottom.y--;
		auto index = indexByPos(posBottom);
		hiddenSides[index] |= BlockSide::Top;
	}
	if (pos.y < ChunkSize - 1 && nonOpaque & BlockSide::Top)
	{
		auto posTop = pos;
		posTop.y++;
		auto index = indexByPos(posTop);
		hiddenSides[index] |= BlockSide::Bottom;
	}
	if (pos.z > 0 && nonOpaque & BlockSide::Front)
	{
		auto posBack = pos;
		posBack.z--;
		auto index = indexByPos(posBack);
		hiddenSides[index] |= BlockSide::Back;
	}
	if (pos.z < ChunkSize - 1 && nonOpaque & BlockSide::Back)
	{
		auto posFront = pos;
		posFront.z++;
		auto index = indexByPos(posFront);
		hiddenSides[index] |= BlockSide::Front;
	}
}
