#include "./DeviceAddon.hpp"
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

VulkanDeviceAddon::VulkanDeviceAddon(std::weak_ptr<VulkanPhysicalDevice> physicalDevice) :
	physicalDevice_(physicalDevice)
{
	
}

VulkanDeviceAddon::~VulkanDeviceAddon()
{
	
}

VulkanAddonType VulkanDeviceAddon::type() const
{
	return VulkanAddonType::Device;
}