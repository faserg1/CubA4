#include "./VulkanSwapchainBuilder.hpp"
#include "./VulkanDevice.hpp"
#include "./VulkanSwapchain.hpp"
#include "./VulkanSurface.hpp"

#include <config/IRenderConfig.hpp>
#include <vulkan/vulkan.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::config;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			struct VulkanSwapchainBuilderData
			{
				VkSurfaceCapabilitiesKHR caps;
				std::vector<VkSurfaceFormatKHR> surfaceFormats;
				std::vector<VkPresentModeKHR> presentModes;
			};
		}
	}
}

VulkanSwapchainBuilder::VulkanSwapchainBuilder(
	std::shared_ptr<const VulkanDevice> device, std::weak_ptr<const VulkanSurface> surface, std::shared_ptr<const IRenderConfig> config) :
	data_(std::make_shared<VulkanSwapchainBuilderData>()), device_(device), surface_(surface), config_(config)
{
	if (auto surface = surface_.lock())
	{
		auto dev = device_->getPhysicalDevice();
		auto sf = surface->getSurface();
		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, sf, &data_->caps) != VK_SUCCESS)
			throw std::runtime_error("Can't get surface capabilities");
		uint32_t surfaceFormatCount;
		if (vkGetPhysicalDeviceSurfaceFormatsKHR(dev, sf, &surfaceFormatCount, nullptr) != VK_SUCCESS)
			throw std::runtime_error("Can't get surface formats");
		data_->surfaceFormats.resize(surfaceFormatCount);
		if (vkGetPhysicalDeviceSurfaceFormatsKHR(dev, sf, &surfaceFormatCount, data_->surfaceFormats.data()) != VK_SUCCESS)
			throw std::runtime_error("Can't get surface formats");
		uint32_t surfacePresentModeCount;
		if (vkGetPhysicalDeviceSurfacePresentModesKHR(dev, sf, &surfacePresentModeCount, nullptr) != VK_SUCCESS)
			throw std::runtime_error("Can't get surface present modes");
		data_->surfaceFormats.resize(surfaceFormatCount);
		if (vkGetPhysicalDeviceSurfacePresentModesKHR(dev, sf, &surfacePresentModeCount, data_->presentModes.data()) != VK_SUCCESS)
			throw std::runtime_error("Can't get surface present modes");
	}
	else
		throw std::runtime_error("Can't get surface for swapchain!");
}

VulkanSwapchainBuilder::~VulkanSwapchainBuilder()
{
	
}

std::shared_ptr<VulkanSwapchain> VulkanSwapchainBuilder::build()
{
	std::shared_ptr<const VulkanSurface> surface = surface_.lock();
	if (!surface)
		throw std::runtime_error("Can't get surface for swapchain!");
	VkSwapchainCreateInfoKHR swapchainInfo = {};
	swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainInfo.surface = surface->getSurface();
	swapchainInfo.minImageCount = 2;
	VkFormat choosedFormat = {};
	auto formats = data_->surfaceFormats;
	std::remove_if(formats.begin(), formats.end(), [](const VkSurfaceFormatKHR &format) -> bool
	{
		return format.colorSpace != VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	});
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
	swapchainInfo.imageFormat = choosedFormat;
	swapchainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapchainInfo.imageExtent = data_->caps.currentExtent;
	swapchainInfo.imageArrayLayers = 1;
	swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainInfo.preTransform = data_->caps.currentTransform;
	swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	swapchainInfo.clipped = VK_FALSE;
	VkSwapchainKHR swapchain;
	if (vkCreateSwapchainKHR(device_->getDevice(), &swapchainInfo, nullptr, &swapchain) != VK_SUCCESS)
		throw std::runtime_error("Cannot create swapchain");
	return std::make_shared<VulkanSwapchain>(swapchain, swapchainInfo.imageExtent, swapchainInfo.minImageCount, swapchainInfo.imageFormat);
}

std::shared_ptr<VulkanSwapchain> VulkanSwapchainBuilder::rebuild(std::shared_ptr<const VulkanSwapchain> oldSwapchain)
{
	return std::shared_ptr<VulkanSwapchain>();
}

void VulkanSwapchainBuilder::destroy(std::shared_ptr<const VulkanSwapchain> swapchain)
{
	vkDestroySwapchainKHR(device_->getDevice(), swapchain->getSwapchain(), nullptr);
}