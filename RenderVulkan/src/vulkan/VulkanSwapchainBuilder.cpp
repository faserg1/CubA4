#include "./VulkanSwapchainBuilder.hpp"
#include "./VulkanDevice.hpp"
#include "./VulkanSwapchain.hpp"
#include "./VulkanSurface.hpp"

#include <config/IRenderConfig.hpp>
#include <vulkan/vulkan.h>
#include <stdexcept>
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
		if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device_->getPhysicalDevice(), surface->getSurface(), &data_->caps) != VK_SUCCESS)
			throw std::runtime_error("Can't get surface capabilities");
	}
	else
		throw std::runtime_error("Can't get surface for swapchain!");
}

VulkanSwapchainBuilder::~VulkanSwapchainBuilder()
{
	
}

std::shared_ptr<VulkanSwapchain> VulkanSwapchainBuilder::build()
{
	return std::shared_ptr<VulkanSwapchain>();
}

std::shared_ptr<VulkanSwapchain> VulkanSwapchainBuilder::rebuild(std::shared_ptr<const VulkanSwapchain> oldSwapchain)
{
	return std::shared_ptr<VulkanSwapchain>();
}

void VulkanSwapchainBuilder::destroy(std::shared_ptr<const VulkanSwapchain> swapchain)
{
	vkDestroySwapchainKHR(device_->getDevice(), swapchain->getSwapchain(), nullptr);
}