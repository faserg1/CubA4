#include "./PhysicalDevice.hpp"
using namespace CubA4::render::vulkan;

VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice physicalDevice) :
	physicalDevice_(physicalDevice)
{
	
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
	
}

VkPhysicalDevice VulkanPhysicalDevice::getPhysicalDevice() const
{
	return physicalDevice_;
}