#include "./VulkanSwapchainExtension.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

VulkanSwapchainExtension::VulkanSwapchainExtension()
{
	
}

VulkanSwapchainExtension::~VulkanSwapchainExtension()
{
	
}

std::vector<std::string> VulkanSwapchainExtension::names() const
{
	return { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
}

void VulkanSwapchainExtension::init(std::shared_ptr<const VulkanInstance> instance)
{

}

void VulkanSwapchainExtension::destroy(std::shared_ptr<const VulkanInstance> instance)
{

}