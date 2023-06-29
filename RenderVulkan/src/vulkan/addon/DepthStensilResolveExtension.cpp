#include <vulkan/addon/DepthStensilResolveExtension.hpp>
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

DepthStensilResolveExtension::DepthStensilResolveExtension(std::weak_ptr<PhysicalDevice> physicalDevice) :
	DeviceExtension(physicalDevice)
{
	
}

DepthStensilResolveExtension::~DepthStensilResolveExtension()
{
	
}

std::vector<std::string> DepthStensilResolveExtension::names() const
{
	return { VK_KHR_DEPTH_STENCIL_RESOLVE_EXTENSION_NAME };
}

void DepthStensilResolveExtension::init(std::shared_ptr<const Device> instance)
{

}

void DepthStensilResolveExtension::destroy(std::shared_ptr<const Device> instance)
{

}

void DepthStensilResolveExtension::added(DeviceBuilder &builder)
{

}