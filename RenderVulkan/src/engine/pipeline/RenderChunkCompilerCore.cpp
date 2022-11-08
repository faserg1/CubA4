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

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;
using namespace CubA4::model;

constexpr const unsigned short commandPoolsCount = 64;

RenderChunkCompilerCore::RenderChunkCompilerCore(std::shared_ptr<const Device> device) :
	device_(device), memManager_(std::make_shared<MemoryManager>(device))
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
	auto hiddenSides = compileHiddenSides(chunk);
	struct Def
	{
		std::vector<BlockPtr> blocks;
		std::string materialId;
	};
	using Key = std::shared_ptr<const CubA4::render::engine::material::IMaterial>;
	std::unordered_map<Key, Def> materialsToDefMap;
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
	for (const auto &pair : materialsToDefMap)
	{
		auto compiledModel = compileModelByMaterial(chunk, pair.second.materialId, pair.second.blocks, hiddenSides);
		auto material = std::dynamic_pointer_cast<const CubA4::render::engine::material::Material>(pair.first);
		models.insert(std::make_pair(material, compiledModel));
	}
	return std::move(models);
}

RenderChunkCompilerCore::RenderModelPtr RenderChunkCompilerCore::compileModelByMaterial(std::shared_ptr<const CubA4::world::IChunk> chunk, const std::string &material, std::vector<BlockPtr> blocks, const HiddenSides &hiddenSides)
{
	model::ModelCompiler compiler;
	for (auto block : blocks)
	{
		auto ranges = chunk->getChunkRanges(block);
		for (auto range : ranges)
		{
			for (auto blockPos : *range)
			{
				// TODO: Fill with data
				CubA4::world::BlockData data;
				auto index = blockPos.y * world::ChunkSize * world::ChunkSize + blockPos.y * world::ChunkSize + blockPos.x;
				auto model = block->getRenderModelDefinition();
				auto faces = model->getFaces(material, hiddenSides[index], data);
				compiler.addFaces(model, faces, blockPos);
			}
		}
	}
	return compiler.compile(material, nullptr);
}

RenderChunkCompilerCore::HiddenSides RenderChunkCompilerCore::compileHiddenSides(std::shared_ptr<const CubA4::world::IChunk> chunk) const
{
	RenderChunkCompilerCore::HiddenSides hiddenSides;
	for (auto range : chunk->getChunkRanges())
	{
		auto block = range->getBlock();
		for (auto blockPos : *range)
		{
			// TODO: Fill with data
			CubA4::world::BlockData data;
			auto index = blockPos.y * world::ChunkSize * world::ChunkSize + blockPos.y * world::ChunkSize + blockPos.x;
			hiddenSides[index] |= block->getRenderModelDefinition()->getNonOpaqueSide(data);
		}
	}
	return std::move(hiddenSides);
}