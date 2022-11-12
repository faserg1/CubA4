#include "./RenderChunkCompilerCore.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/DebugMarker.hpp"
#include <world/IChunk.hpp>
#include <object/IBlock.hpp>
#include "../memory/MemoryManager.hpp"
#include "../model/ModelCompiler.hpp"
#include <algorithm>
#include <execution>
#include <string>
#include <cmath>
#include <unordered_map>
#include <fmt/format.h>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;
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
		descriptorPools_.push_back(util::createSharedVulkanObject(pool, deleter));
	}
}

RenderChunkCompilerCore::RenderModels RenderChunkCompilerCore::compileBlocks(std::shared_ptr<const CubA4::world::IChunk> chunk)
{
	RenderModels models;
	auto cpos = chunk->getChunkPos();
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Compiling chunk {}, {}, {}", cpos.x, cpos.y, cpos.z));
	auto hiddenSides = compileHiddenSides(chunk);
	struct Def
	{
		std::vector<BlockPtr> blocks;
		std::string materialId;
	};
	using Key = std::shared_ptr<const CubA4::render::engine::material::IMaterial>;
	std::unordered_map<Key, Def> materialsToDefMap;
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Searching for materials in chunk {}, {}, {}", cpos.x, cpos.y, cpos.z));

	for (auto block : chunk->getUsedBlocks())
	{
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
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Compiling chunk models in chunk {}, {}, {}", cpos.x, cpos.y, cpos.z));

	for (const auto &pair : materialsToDefMap)
	{
		auto compiledModel = compileModelByMaterial(chunk, pair.second.materialId, pair.second.blocks, hiddenSides);
		if (!compiledModel)
			continue;
		auto material = std::dynamic_pointer_cast<const CubA4::render::engine::material::Material>(pair.first);
		models.insert(std::make_pair(material, compiledModel));
	}
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Compiled chunk {}, {}, {}", cpos.x, cpos.y, cpos.z));

	return std::move(models);
}

RenderChunkCompilerCore::RenderModelPtr RenderChunkCompilerCore::compileModelByMaterial(std::shared_ptr<const CubA4::world::IChunk> chunk, const std::string &material, std::vector<BlockPtr> blocks, const HiddenSides &hiddenSides)
{
	auto cpos = chunk->getChunkPos();
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Models collecting {}, {}, {}", cpos.x, cpos.y, cpos.z));
	model::ModelCompiler compiler;
	for (auto block : blocks)
	{
		auto ranges = chunk->getChunkRanges(block);
		for (auto range : ranges)
		{
			for (auto blockPos : *range)
			{
				// TODO: Fill with data
				BlockData data;
				auto index = indexByPos(blockPos);
				auto model = block->getRenderModelDefinition();
				auto faces = model->getFaces(material, hiddenSides[index], data);
				compiler.addFaces(model, std::move(faces), blockPos);
			}
		}
	}
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Model building {}, {}, {}", cpos.x, cpos.y, cpos.z));
	auto model = compiler.compile(material, modelManager_);;
	core_->getLogger()->log(logging::LogSourceSystem::Render, "RenderChunkCompilerCore", logging::LogLevel::Debug, fmt::format("Model building done {}, {}, {}", cpos.x, cpos.y, cpos.z));
	return model;
}

RenderChunkCompilerCore::HiddenSides RenderChunkCompilerCore::compileHiddenSides(std::shared_ptr<const IChunk> chunk) const
{
	RenderChunkCompilerCore::HiddenSides hiddenSides;
	hiddenSides.fill(0);
	for (auto range : chunk->getChunkRanges())
	{
		auto block = range->getBlock();
		for (auto blockPos : *range)
		{
			// TODO: Fill with data
			BlockData data;
			auto nonOpaque = block->getRenderModelDefinition()->getNonOpaqueSide(data);
			hideFrom(hiddenSides, blockPos, nonOpaque);
		}
	}
	return std::move(hiddenSides);
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
	if (pos.x < ChunkSize && nonOpaque & BlockSide::Right)
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
	if (pos.y < ChunkSize && nonOpaque & BlockSide::Top)
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
	if (pos.z < ChunkSize && nonOpaque & BlockSide::Back)
	{
		auto posFront = pos;
		posFront.z++;
		auto index = indexByPos(posFront);
		hiddenSides[index] |= BlockSide::Front;
	}
}

size_t RenderChunkCompilerCore::indexByPos(const BlockInChunkPos &pos)
{
	return (pos.z * ChunkSize * ChunkSize) + (pos.y * ChunkSize) + pos.x;
}