#include "./RenderChunkCompilerCore.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/DebugMarker.hpp"
#include <world/IChunk.hpp>
#include "../MemoryManager.hpp"
#include <algorithm>
#include <string>
#include <cmath>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;

constexpr const unsigned short commandPoolsCount = 64;

RenderChunkCompilerCore::RenderChunkCompilerCore(std::shared_ptr<const Device> device) :
	device_(device), memManager_(std::make_shared<MemoryManager>(device))
{
	initCommandPools();
}

RenderChunkCompilerCore::~RenderChunkCompilerCore()
{
	
}

void RenderChunkCompilerCore::initCommandPools()
{
	commandPools_.reserve(commandPoolsCount);
	for (unsigned short i = 0; i < commandPoolsCount; i++)
		commandPools_.push_back(std::make_shared<CommandPool>(device_, 0));
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