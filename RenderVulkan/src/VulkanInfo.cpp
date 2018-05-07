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

std::string CubA4::render::VulkanInfo::getRenderEngineId() const
{
	return "Vulkan";
}

RenderEngine * CubA4::render::VulkanInfo::getRenderEngine()
{
	return nullptr;
}

int64_t CubA4::render::VulkanInfo::getSDLWindowFlags() const
{
	return SDL_WINDOW_VULKAN;
}
