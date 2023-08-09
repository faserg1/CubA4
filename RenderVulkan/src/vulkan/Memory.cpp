#include "./Memory.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

Memory::Memory(std::shared_ptr<const Device> device, VkDeviceMemory memory, VkDeviceSize size, VkMemoryPropertyFlags flags, uint32_t memoryTypeIndex) :
	device_(device), memory_(memory), size_(size), flags_(flags), memoryTypeIndex_(memoryTypeIndex)
{	
}

Memory::~Memory()
{
	vkFreeMemory(device_->getDevice(), memory_, nullptr);
}

bool Memory::isMappable() const
{
	return flags_ & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
}

VkDeviceMemory Memory::getMemory() const
{
	return memory_;
}

VkDeviceSize Memory::getSize() const
{
	return size_;
}

VkMemoryPropertyFlags Memory::getFlags() const
{
	return flags_;
}

uint32_t Memory::getMemoryTypeIndex() const
{
	return memoryTypeIndex_;
}

std::shared_ptr<void> Memory::map(VkDeviceSize offset, VkDeviceSize size) const
{
	void *ptr;
	if (vkMapMemory(device_->getDevice(), memory_, offset, size, 0, &ptr) != VK_SUCCESS)
		return {};
	auto mem = shared_from_this();
	return std::shared_ptr<void>(ptr, [mem](void *ptr)
	{
		vkUnmapMemory(mem->device_->getDevice(), mem->getMemory());
	});
}

void Memory::flush(VkDeviceSize offset, VkDeviceSize size) const
{
	VkMappedMemoryRange range {
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = memory_,
		.offset = offset,
		.size = size,
	};
	vkFlushMappedMemoryRanges(device_->getDevice(), 1, &range);
}