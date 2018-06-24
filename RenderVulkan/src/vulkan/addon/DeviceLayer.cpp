#include "./VulkanDeviceLayer.hpp"
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

VulkanDeviceLayer::VulkanDeviceLayer(std::weak_ptr<VulkanPhysicalDevice> physicalDevice) :
	VulkanDeviceAddon(physicalDevice)
{
	
}

VulkanDeviceLayer::~VulkanDeviceLayer()
{
	
}

