#include "./Device.hpp"
using namespace CubA4::render::vulkan;

Device::Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue) :
	device_(device), physicalDevice_(physicalDevice), queue_(queue), marker_(*this)
{
	marker_.setName(device_, "Default logical device");
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

DebugMarker &Device::getMarker() const
{
	return marker_;
}