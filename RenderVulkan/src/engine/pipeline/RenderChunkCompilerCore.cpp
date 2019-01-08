#include "./RenderChunkCompilerCore.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/DebugMarker.hpp"
#include <world/IChunk.hpp>
#include "../memory/MemoryManager.hpp"
#include <algorithm>
#include <string>
#include <cmath>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;

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