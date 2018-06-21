#include "./Device.hpp" 
using namespace CubA4::render::vulkan;

Device::Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue) :
	device_(device), physicalDevice_(physicalDevice), queue_(queue)
{
	
}

Device::~Device()
{
	
}

VkDevice Device::getDevice() const
{
	return device_;
}

VkPhysicalDevice Device::getPhysicalDevice() const
{
	return physicalDevice_;
}

VkQueue Device::getQueue() const
{
	return queue_;
}