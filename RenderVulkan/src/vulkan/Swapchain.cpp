#include "./VulkanSwapchain.hpp"
using namespace CubA4::render::vulkan;

VulkanSwapchain::VulkanSwapchain(VkSwapchainKHR swapchain, VkExtent2D res, uint32_t imageCount, VkFormat format) :
	swapchain_(swapchain), resolution_(res), imageCount_(imageCount), format_(format)
{
	
}

VulkanSwapchain::~VulkanSwapchain()
{
	
}

VkSwapchainKHR VulkanSwapchain::getSwapchain() const
{
	return swapchain_;
}

VkExtent2D VulkanSwapchain::getResolution() const
{
	return resolution_;
}

uint32_t VulkanSwapchain::getImageCount() const
{
	return imageCount_;
}

VkFormat VulkanSwapchain::getFormat() const
{
	return format_;
}