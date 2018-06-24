#include "./Device.hpp"
using namespace CubA4::render::vulkan;

VulkanDevice::VulkanDevice(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue) :
	device_(device), physicalDevice_(physicalDevice), queue_(queue)
{
	
}

VulkanDevice::~VulkanDevice()
{
	
}

VkDevice VulkanDevice::getDevice() const
{
	return device_;
}

VkPhysicalDevice VulkanDevice::getPhysicalDevice() const
{
	return physicalDevice_;
}

VkQueue VulkanDevice::getQueue() const
{
	return queue_;
}