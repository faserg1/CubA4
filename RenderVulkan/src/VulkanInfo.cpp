#include "VulkanInfo.hpp"
#include <SDL_vulkan.h>
#include "engine/VulkanRenderEngine.hpp"

using namespace CubA4::render;

VulkanInfo::VulkanInfo()
{

}

VulkanInfo::~VulkanInfo()
{

}

void VulkanInfo::init(std::shared_ptr<const CubA4::core::info::IApplicationInfo> info)
{
	info_ = info;
	engine_ = std::make_shared<engine::VulkanRenderEngine>(info_);
}

void VulkanInfo::destroy()
{

}

std::string VulkanInfo::getRenderEngineId() const
{
	return "Vulkan";
}

std::shared_ptr<engine::IRenderEngine> VulkanInfo::getRenderEngine()
{
	return engine_;
}

int64_t VulkanInfo::getSDLWindowFlags() const
{
	return SDL_WINDOW_VULKAN;
}
