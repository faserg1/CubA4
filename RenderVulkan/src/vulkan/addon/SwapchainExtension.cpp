#include "./SwapchainExtension.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

SwapchainExtension::SwapchainExtension(std::weak_ptr<PhysicalDevice> physicalDevice) :
	DeviceExtension(physicalDevice)
{
	
}

SwapchainExtension::~SwapchainExtension()
{
	
}

std::vector<std::string> SwapchainExtension::names() const
{
	return { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
}

void SwapchainExtension::init(std::shared_ptr<const Device> instance)
{

}

void SwapchainExtension::destroy(std::shared_ptr<const Device> instance)
{

}

void SwapchainExtension::added(DeviceBuilder &builder)
{

}