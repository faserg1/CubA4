#include "./Surface.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;

Surface::Surface(VkSurfaceKHR surface) : surface_(surface)
{
	
}

Surface::~Surface()
{
	
}

VkSurfaceKHR Surface::getSurface() const
{
	return surface_;
}

