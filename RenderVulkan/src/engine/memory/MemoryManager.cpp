#include "./MemoryManager.hpp"
#include "./MemoryAllocator.hpp"
#include "./MemoryBlock.hpp"
#include "./MemoryPart.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

namespace
{
	uint64_t calcAlign(uint64_t size, uint64_t align)
	{
		if (!size)
			return 0;
		auto res = size % align;
		if (res == 0)
			return size;
		return size + align - res;
	}
}

MemoryManager::MemoryManager(std::shared_ptr<const Device> device, uint32_t blockSize) :
	device_(device), blockSize_(blockSize), allocator_(std::make_shared<MemoryAllocator>(device))
{
	
}

MemoryManager::~MemoryManager()
{
	
}

uint32_t MemoryManager::calcAlign(uint32_t size, uint32_t align)
{
	return static_cast<uint32_t>(::calcAlign(size, align));
}

std::shared_ptr<const IMemoryPart> MemoryManager::allocatePart(uint64_t size, uint64_t alignment, uint32_t supportedTypes)
{
	if (size > blockSize_)
		return {};
	for (auto block : memoryBlocks_)
	{
		const uint32_t memoryTypeBits = (1 << block->getMemoryTypeIndex());
		const bool isRequiredMemoryType = supportedTypes & memoryTypeBits;
		if (!isRequiredMemoryType)
			continue;
		auto memBlock = std::dynamic_pointer_cast<MemoryBlock>(block);
		auto part = memBlock->allocatePart(size, alignment);
		if (!part)
			continue;
		return part;
	}
	auto newBlock = allocateBlock(supportedTypes);
	memoryBlocks_.push_back(newBlock);
	auto newMemBlock = std::dynamic_pointer_cast<MemoryBlock>(newBlock);
	return newMemBlock->allocatePart(size, alignment);
}


std::shared_ptr<IMemoryBlock> MemoryManager::allocateBlock(uint32_t supportedTypes)
{
	auto memory = allocator_->allocate(blockSize_, MemoryAllocationPrefered::Device, supportedTypes);
	if (!memory)
		return {};
	return std::make_shared<MemoryBlock>(memory);
}
