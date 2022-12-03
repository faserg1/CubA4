#include "./Surface.hpp"
#include <vulkan/vulkan.h>
#include <stdexcept>
using namespace CubA4::render::vulkan;

Surface::Surface(std::shared_ptr<const Instance> instance, VkSurfaceKHR surface) :
	instance_(instance), surface_(surface)
{
	
}

Surface::~Surface()
{
	vkDestroySurfaceKHR(instance_->getInstance(), surface_, nullptr);
}

void Surface::init(VkPhysicalDevice device)
{
	device_ = device;
	uint32_t surfaceFormatCount;
	if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface_, &surfaceFormatCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Can't get surface formats");
	surfaceFormats_.resize(surfaceFormatCount);
	if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface_, &surfaceFormatCount, surfaceFormats_.data()) != VK_SUCCESS)
		throw std::runtime_error("Can't get surface formats");
	uint32_t surfacePresentModeCount;
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface_, &surfacePresentModeCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Can't get surface present modes");
	surfaceFormats_.resize(surfaceFormatCount);
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface_, &surfacePresentModeCount, presentModes_.data()) != VK_SUCCESS)
		throw std::runtime_error("Can't get surface present modes");
}

VkSurfaceKHR Surface::getSurface() const
{
	return surface_;
}

VkSurfaceCapabilitiesKHR Surface::getCapabilities() const
{
	VkSurfaceCapabilitiesKHR caps;
	if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device_, surface_, &caps) != VK_SUCCESS)
		throw std::runtime_error("Can't get surface capabilities");
	return caps;
}

const std::vector<VkSurfaceFormatKHR> &Surface::surfaceFormats() const
{
	return surfaceFormats_;
}

const std::vector<VkPresentModeKHR> &Surface::presentModes() const
{
	return presentModes_;
}