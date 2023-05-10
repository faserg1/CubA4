#include "./PhysicalDevice.hpp"
using namespace CubA4::render::vulkan;

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) :
	physicalDevice_(physicalDevice)
{
	vkGetPhysicalDeviceProperties(physicalDevice_, &properties_);
}

PhysicalDevice::~PhysicalDevice()
{
	
}

VkPhysicalDevice PhysicalDevice::getPhysicalDevice() const
{
	return physicalDevice_;
}

const VkPhysicalDeviceProperties &PhysicalDevice::getProperties() const
{
	return properties_;
}