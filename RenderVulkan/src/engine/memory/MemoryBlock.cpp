#include "./MemoryBlock.hpp"
#include "./MemoryPart.hpp"
#include "../../vulkan/Memory.hpp"
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::vulkan;

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

MemoryBlock::MemoryBlock(std::shared_ptr<Memory> memory) :
	memory_(memory)
{

}

VkMemoryPropertyFlags MemoryBlock::getFlags() const
{
	return memory_->getFlags();
}

uint32_t MemoryBlock::getMemoryTypeIndex() const
{
	return memory_->getMemoryTypeIndex();
}

std::shared_ptr<Memory> MemoryBlock::getMemory() const
{
	return memory_;
}

std::shared_ptr<MemoryPart> MemoryBlock::allocatePart(uint64_t size, uint64_t alignment)
{
	if (!parts_.size())
	{
		auto part = std::make_shared<MemoryPart>(shared_from_this(), 0, size);
		parts_.push_back(part);
		return part;
	}
	VkDeviceSize lastOffset = 0;
	auto partIterator = parts_.begin();
	for (auto part : parts_)
	{
		auto locked = part.lock();
		auto partOffset = locked->getOffset();
		auto lastOffsetTemp = lastOffset;
		lastOffset = locked->getOffset() + locked->getSize();

		if (calcAlign(lastOffsetTemp, alignment) + size <= partOffset)
		{
			auto offset = calcAlign(lastOffsetTemp, alignment);
			auto part = std::make_shared<MemoryPart>(shared_from_this(), offset, size);
			parts_.insert(partIterator, part);
			return part;
		}
		partIterator++;
	}
	if (calcAlign(lastOffset, alignment) + size <= memory_->getSize())
	{
		auto offset = calcAlign(lastOffset, alignment);
		auto part = std::make_shared<MemoryPart>(shared_from_this(), offset, size);
		parts_.push_back(part);
		return part;
	}
	return {};
}

void MemoryBlock::freePart(const MemoryPart *part)
{
	parts_.remove_if([part](std::weak_ptr<MemoryPart> value) -> bool
	{
		auto locked = value.lock();
		if (!locked)
			return true;
		return locked->getOffset() == part->getOffset() && locked->getSize() == part->getSize();
	});
}
