#include "./Swapchain.hpp" 
using namespace CubA4::render::vulkan;

Swapchain::Swapchain(VkSwapchainKHR swapchain, VkExtent2D res, uint32_t imageCount, VkFormat format) :
	swapchain_(swapchain), resolution_(res), imageCount_(imageCount), format_(format)
{
	
}

Swapchain::~Swapchain()
{
	
}

VkSwapchainKHR Swapchain::getSwapchain() const
{
	return swapchain_;
}

VkExtent2D Swapchain::getResolution() const
{
	return resolution_;
}

uint32_t Swapchain::getImageCount() const
{
	return imageCount_;
}

VkFormat Swapchain::getFormat() const
{
	return format_;
}