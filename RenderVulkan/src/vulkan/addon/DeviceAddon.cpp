#include "./DeviceAddon.hpp"
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

DeviceAddon::DeviceAddon(std::weak_ptr<PhysicalDevice> physicalDevice) :
	physicalDevice_(physicalDevice)
{
	
}

DeviceAddon::~DeviceAddon()
{
	
}

AddonType DeviceAddon::type() const
{
	return AddonType::Device;
}