#include "./VulkanDevice.hpp"
using namespace CubA4::render::vulkan;

VulkanDevice::VulkanDevice(VkDevice device, VkQueue queue) :
	device_(device), queue_(queue)
{
	
}

VulkanDevice::~VulkanDevice()
{
	
}

VkDevice VulkanDevice::getDevice() const
{
	return device_;
}

VkQueue VulkanDevice::getQueue() const
{
	return queue_;
}