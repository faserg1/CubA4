#include "./Swapchain.hpp"
using namespace CubA4::render::vulkan;

Swapchain::Swapchain(std::shared_ptr<const Device> device, VkSwapchainKHR swapchain, VkExtent2D res, uint32_t imageCount, VkFormat format) :
	device_(device), swapchain_(swapchain), resolution_(res), imageCount_(imageCount), format_(format)
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

std::vector<VkImage> Swapchain::getImages() const
{
	std::vector<VkImage> images(imageCount_);
	uint32_t imageCount = imageCount_;
	vkGetSwapchainImagesKHR(device_->getDevice(), swapchain_, &imageCount, images.data());
	return std::move(images);
}