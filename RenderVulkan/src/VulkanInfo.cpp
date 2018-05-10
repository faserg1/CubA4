#include "VulkanInfo.hpp"
#include <vulkan/vulkan.h>
#include <SDL_video.h>

using namespace CubA4::render;

VulkanInfo::VulkanInfo()
{

}

VulkanInfo::~VulkanInfo()
{

}

std::string VulkanInfo::getRenderEngineId() const
{
	return "Vulkan";
}

IRenderEngine *VulkanInfo::getRenderEngine()
{
	return nullptr;
}

int64_t VulkanInfo::getSDLWindowFlags() const
{
	return SDL_WINDOW_VULKAN;
}
