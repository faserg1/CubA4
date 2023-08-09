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

std::shared_ptr<const IMemoryPart> MemoryManager::allocatePart(uint64_t size, uint64_t alignment, uint32_t supportedTypes, MemoryAllocationPrefered preference)
{
	std::lock_guard<std::mutex> lockGuard(mutex_);
	if (size > blockSize_)
	{
		auto newBlock = allocateBlockSize(size, supportedTypes, preference);
		memoryBlocks_.push_back(newBlock);
		auto newMemBlock = std::dynamic_pointer_cast<MemoryBlock>(newBlock);
		return newMemBlock->allocatePart(size, alignment);
	}
	for (auto block : memoryBlocks_)
	{
		const uint32_t memoryTypeBits = (1 << block->getMemoryTypeIndex());
		const bool isRequiredMemoryType = supportedTypes & memoryTypeBits;
		if (!isRequiredMemoryType)
			continue;
		const auto requiredFlags = allocator_->getPreferenceFlags(preference);
		if (!(block->getFlags() & requiredFlags))
			continue;
		auto memBlock = std::dynamic_pointer_cast<MemoryBlock>(block);
		auto part = memBlock->allocatePart(size, alignment);
		if (!part)
			continue;
		return part;
	}
	auto newBlock = allocateBlock(supportedTypes, preference);
	memoryBlocks_.push_back(newBlock);
	auto newMemBlock = std::dynamic_pointer_cast<MemoryBlock>(newBlock);
	return newMemBlock->allocatePart(size, alignment);
}

std::shared_ptr<const IMemoryPart> MemoryManager::allocateAndBindPart(VkBuffer buffer, MemoryAllocationPrefered preference)
{
	VkBufferMemoryRequirementsInfo2 info {
		.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2,
		.buffer = buffer
	};
	VkMemoryRequirements2 memReq = {};
	memReq.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
	vkGetBufferMemoryRequirements2(device_->getDevice(), &info, &memReq);

	auto part = allocatePart(memReq.memoryRequirements.size, memReq.memoryRequirements.alignment, memReq.memoryRequirements.memoryTypeBits, preference);
	vkBindBufferMemory(device_->getDevice(), buffer, part->getMemory()->getMemory(), part->getOffset());
	return part;
}

std::shared_ptr<const IMemoryPart> MemoryManager::allocateAndBindPart(VkImage image, MemoryAllocationPrefered preference)
{
	VkImageMemoryRequirementsInfo2 info {
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2,
		.image = image
	};
	VkMemoryRequirements2 memReq = {};
	vkGetImageMemoryRequirements2(device_->getDevice(), &info, &memReq);

	auto part = allocatePart(memReq.memoryRequirements.size, memReq.memoryRequirements.alignment, memReq.memoryRequirements.memoryTypeBits, preference);
	vkBindImageMemory(device_->getDevice(), image, part->getMemory()->getMemory(), part->getOffset());
	return part;
}

std::shared_ptr<IMemoryBlock> MemoryManager::allocateBlock(uint32_t supportedTypes, MemoryAllocationPrefered preference)
{
	auto memory = allocator_->allocate(blockSize_, preference, supportedTypes);
	if (!memory)
		return {};
	return std::make_shared<MemoryBlock>(memory);
}

std::shared_ptr<IMemoryBlock> MemoryManager::allocateBlockSize(size_t size, uint32_t supportedTypes, MemoryAllocationPrefered preference)
{
	auto memory = allocator_->allocate(size, preference, supportedTypes);
	if (!memory)
		return {};
	return std::make_shared<MemoryBlock>(memory);
}