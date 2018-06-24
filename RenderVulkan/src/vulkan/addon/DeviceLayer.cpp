#include "./DeviceLayer.hpp"
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

DeviceLayer::DeviceLayer(std::weak_ptr<PhysicalDevice> physicalDevice) :
	DeviceAddon(physicalDevice)
{
	
}

DeviceLayer::~DeviceLayer()
{
	
}

