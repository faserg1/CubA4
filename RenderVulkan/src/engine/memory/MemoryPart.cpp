#include "./MemoryPart.hpp"
#include "./MemoryBlock.hpp"
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