#include "VulkanInfo.hpp"
#include <SDL_vulkan.h>
#include "engine/RenderEngine.hpp"

using namespace CubA4::render;

VulkanInfo::VulkanInfo()
{

}

VulkanInfo::~VulkanInfo()
{

}

void VulkanInfo::init(std::shared_ptr<const CubA4::core::info::IApplicationInfo> info, std::shared_ptr<const CubA4::core::ICore> core)
{
	info_ = info;
	core_ = core;
	engine_ = std::make_shared<engine::VulkanRenderEngine>(info_, core_);
}

void VulkanInfo::destroy()
{

}

std::string VulkanInfo::getRenderEngineId() const
{
	return "vulkan";
}

std::shared_ptr<engine::IRenderEngine> VulkanInfo::getRenderEngine()
{
	return engine_;
}

uint32_t VulkanInfo::getSDLWindowFlags() const
{
	return SDL_WINDOW_VULKAN;
}
