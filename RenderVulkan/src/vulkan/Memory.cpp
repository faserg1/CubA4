#include "./Memory.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

Memory::Memory(std::shared_ptr<const Device> device, VkDeviceMemory memory, VkDeviceSize size, VkMemoryPropertyFlags flags) :
	device_(device), memory_(memory), size_(size), flags_(flags)
{	
}

Memory::~Memory()
{
	vkFreeMemory(device_->getDevice(), memory_, nullptr);
}

std::shared_ptr<Memory> Memory::create(std::shared_ptr<const Device> device, VkDeviceMemory memory, VkDeviceSize size, VkMemoryPropertyFlags flags)
{
	auto ptr = std::shared_ptr<Memory>(new Memory(device, memory, size, flags));
	ptr->self_ = ptr;
	return ptr;
}

bool Memory::isMappable()
{
	return flags_ & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
}

VkDeviceMemory Memory::getMemory()
{
	return memory_;
}

VkDeviceSize Memory::getSize()
{
	return size_;
}

VkMemoryPropertyFlags Memory::getFlags()
{
	return flags_;
}

std::shared_ptr<void> Memory::map(VkDeviceSize offset, VkDeviceSize size)
{
	void *ptr;
	if (vkMapMemory(device_->getDevice(), memory_, offset, size, 0, &ptr) != VK_SUCCESS)
		return {};
	auto mem = self_.lock();
	return std::shared_ptr<void>(ptr, [mem](void *ptr)
	{
		vkFreeMemory(mem->device_->getDevice(), mem->getMemory(), nullptr);
	});
}