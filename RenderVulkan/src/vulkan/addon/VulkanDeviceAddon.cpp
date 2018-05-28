#include "./VulkanDeviceAddon.hpp"
using namespace CubA4::render::vulkan::addon;

VulkanDeviceAddon::VulkanDeviceAddon()
{
	
}

VulkanDeviceAddon::~VulkanDeviceAddon()
{
	
}

VulkanAddonType VulkanDeviceAddon::type() const
{
	return VulkanAddonType::Device;
}