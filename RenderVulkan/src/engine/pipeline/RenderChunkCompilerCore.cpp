#include "./RenderChunkCompilerCore.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/DebugMarker.hpp"
#include <algorithm>
#include <string>
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;

constexpr const unsigned short commandPoolsCount = 64;

RenderChunkCompilerCore::RenderChunkCompilerCore(std::shared_ptr<const Device> device) :
	device_(device)
{
	initCommandPools();
}

RenderChunkCompilerCore::~RenderChunkCompilerCore()
{
	destroyCommandPools();
}

RenderChunkCompilerCore::CommandPool::CommandPool(VkCommandPool pool) :
	vkPool(pool), available(true)
{

}

RenderChunkCompilerCore::CommandPool::CommandPool(CommandPool &&obj) :
	vkPool(obj.vkPool), available(obj.available.load())
{
	obj.available = false;
}

void RenderChunkCompilerCore::initCommandPools()
{
	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	for (unsigned short i = 0; i < commandPoolsCount; i++)
	{
		VkCommandPool pool;
		vkCreateCommandPool(device_->getDevice(), &info, nullptr, &pool);
		commandPools_.push_back(pool);
		std::string debugName = "RenderChunkCompilerCore CommandPool " + std::to_string(i);
		device_->getMarker().setName(pool, debugName.c_str());
	}
}

void RenderChunkCompilerCore::destroyCommandPools()
{
	for (auto &pool : commandPools_)
	{
		vkDestroyCommandPool(device_->getDevice(), pool.vkPool, nullptr);
	}
}

std::shared_ptr<const RenderChunkCompilerCore::CommandPool> RenderChunkCompilerCore::lockCommandPool(VkCommandPool specialPool)
{
	auto it = commandPools_.end();
	if (specialPool != VK_NULL_HANDLE)
	{
		it = std::find_if(commandPools_.begin(), commandPools_.end(), [specialPool](RenderChunkCompilerCore::CommandPool &pool) -> bool
		{
			return pool.vkPool == specialPool;
		});
		if (it == commandPools_.end())
			return {};
		while (!it->available);
		it->available = false;
		RenderChunkCompilerCore::CommandPool &pool = *it;
		return std::shared_ptr<const RenderChunkCompilerCore::CommandPool>(&pool, [](RenderChunkCompilerCore::CommandPool *pool)
		{
			pool->available = true;
		});
	}
	while (true)
	{
		it = std::find_if(commandPools_.begin(), commandPools_.end(), [](RenderChunkCompilerCore::CommandPool &pool) -> bool
		{
			return pool.available;
		});
		
		if (it == commandPools_.end())
			continue;
		it->available = false;
		RenderChunkCompilerCore::CommandPool &pool = *it;
		return std::shared_ptr<const RenderChunkCompilerCore::CommandPool>(&pool, [](RenderChunkCompilerCore::CommandPool *pool)
		{
			pool->available = true;
		});
	}
}