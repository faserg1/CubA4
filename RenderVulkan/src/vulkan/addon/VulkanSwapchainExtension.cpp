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