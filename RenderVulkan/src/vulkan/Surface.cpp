#include "./Surface.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;

VulkanSurface::VulkanSurface(VkSurfaceKHR surface) : surface_(surface)
{
	
}

VulkanSurface::~VulkanSurface()
{
	
}

VkSurfaceKHR VulkanSurface::getSurface() const
{
	return surface_;
}

