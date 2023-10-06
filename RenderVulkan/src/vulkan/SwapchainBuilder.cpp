#include "./SwapchainBuilder.hpp"
#include "./Device.hpp"
#include "./Swapchain.hpp"
#include "./Surface.hpp"

#include <config/IRenderConfig.hpp>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::config;

SwapchainBuilder::SwapchainBuilder(
	std::shared_ptr<const Device> device, std::weak_ptr<const Surface> surface, std::shared_ptr<IRenderConfig> config) :
	device_(device), surface_(surface), config_(config)
{
	
}

SwapchainBuilder::~SwapchainBuilder()
{
	
}

std::shared_ptr<Swapchain> SwapchainBuilder::build(std::shared_ptr<const Swapchain> oldSwapchain)
{
	std::shared_ptr<const Surface> surface = surface_.lock();
	if (!surface)
		throw std::runtime_error("Can't get surface for swapchain!");
	VkSwapchainCreateInfoKHR swapchainInfo = {};
	swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainInfo.surface = surface->getSurface();
	swapchainInfo.minImageCount = 2;
	swapchainInfo.imageFormat = getFormat();
	swapchainInfo.presentMode = getPresentMode();
	swapchainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapchainInfo.imageExtent = surface->getCapabilities().currentExtent;
	swapchainInfo.imageArrayLayers = 1;
	swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainInfo.preTransform = surface->getCapabilities().currentTransform;
	swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainInfo.clipped = VK_FALSE;
	if (oldSwapchain)
		swapchainInfo.oldSwapchain = oldSwapchain->getSwapchain();
	VkSwapchainKHR swapchain;
	if (vkCreateSwapchainKHR(device_->getDevice(), &swapchainInfo, nullptr, &swapchain) != VK_SUCCESS)
		throw std::runtime_error("Cannot create swapchain");
	device_->getMarker().setName(swapchain, "Default swapchain");
	uint32_t imageCount = 0;
	if (vkGetSwapchainImagesKHR(device_->getDevice(), swapchain, &imageCount, nullptr) != VK_SUCCESS)
	{
		vkDestroySwapchainKHR(device_->getDevice(), swapchain, nullptr);
		throw std::runtime_error("Cannot determinete image count of swapchain");
	}
		

	return std::make_shared<Swapchain>(device_, swapchain, swapchainInfo.imageExtent, imageCount, swapchainInfo.imageFormat);
}

void SwapchainBuilder::destroy(std::shared_ptr<const Swapchain> swapchain)
{
	if (swapchain)
		vkDestroySwapchainKHR(device_->getDevice(), swapchain->getSwapchain(), nullptr);
}

VkFormat SwapchainBuilder::getFormat()
{
	std::shared_ptr<const Surface> surface = surface_.lock();
	if (!surface)
		throw std::runtime_error("Can't get surface for swapchain!");
	VkFormat choosedFormat = {};
	auto formats = surface->surfaceFormats();
	auto toErase = std::remove_if(formats.begin(), formats.end(), [](const VkSurfaceFormatKHR &format) -> bool
	{
		return format.colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	});
	formats.erase(toErase, formats.end());
	std::vector<VkFormat> preferedFormats = { VK_FORMAT_B8G8R8_SRGB, VK_FORMAT_B8G8R8_SRGB, VK_FORMAT_R8G8B8_SRGB, VK_FORMAT_R8G8B8_UNORM };
	for (auto preferedFormat : preferedFormats)
	{
		for (auto format : formats)
		{
			if (format.format == preferedFormat)
				break;
		}
		if (choosedFormat)
			break;
	}
	if (!choosedFormat)
		choosedFormat = formats[0].format;
	return choosedFormat;
}

VkPresentModeKHR SwapchainBuilder::getPresentMode()
{
	VkPresentModeKHR presentMode;
	auto presentMethod = config_->getPresentMethod();
	
	if (presentMethod == "fifo")
		presentMode = VK_PRESENT_MODE_FIFO_KHR;
	else if (presentMethod == "immediate")
		presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	else if (presentMethod == "fifo_relaxed")
		presentMode = VK_PRESENT_MODE_FIFO_RELAXED_KHR;
	else if (presentMethod == "mailbox")
		presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
	else
	{
		presentMode = VK_PRESENT_MODE_FIFO_KHR;
		presentMethod = "fifo";
	}

	config_->setPresentMethod(presentMethod);
	return presentMode;
}