#include "./MemoryPart.hpp"
#include "./MemoryBlock.hpp"
#include <vulkan/Memory.hpp>
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::vulkan;

MemoryPart::MemoryPart(std::shared_ptr<MemoryBlock> block, VkDeviceSize offset, VkDeviceSize size) :
	block_(block), offset_(offset), size_(size)
{
}

MemoryPart::~MemoryPart()
{
	block_->freePart(this);
}

std::shared_ptr<Memory> MemoryPart::getMemory() const
{
	return block_->getMemory();
}

VkDeviceSize MemoryPart::getOffset() const
{
	return offset_;
}

VkDeviceSize MemoryPart::getSize() const
{
	return size_;
}

std::shared_ptr<const IMemoryBlock> MemoryPart::getBlock() const
{
	return block_;
}

std::shared_ptr<void> MemoryPart::map(VkDeviceSize offset, VkDeviceSize size) const
{
	if (size == VK_WHOLE_SIZE)
		size = size_ - offset;
	return block_->map(offset_ + offset, size);
}

void MemoryPart::flush(VkDeviceSize offset, VkDeviceSize size) const
{
	if (size == VK_WHOLE_SIZE)
		size = size_ - offset;
	block_->getMemory()->flush(offset_ + offset, size);
}