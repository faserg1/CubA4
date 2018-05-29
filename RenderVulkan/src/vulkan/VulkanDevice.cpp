#include "./VulkanDevice.hpp"
using namespace CubA4::render::vulkan;

VulkanDevice::VulkanDevice(VkDevice device) :
	device_(device)
{
	
}

VulkanDevice::~VulkanDevice()
{
	
}

VkDevice VulkanDevice::getDevice() const
{
	return device_;
}