#include "./PhysicalDevice.hpp" 
using namespace CubA4::render::vulkan;

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) :
	physicalDevice_(physicalDevice)
{
	
}

PhysicalDevice::~PhysicalDevice()
{
	
}

VkPhysicalDevice PhysicalDevice::getPhysicalDevice() const
{
	return physicalDevice_;
}