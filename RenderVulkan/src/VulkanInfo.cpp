#include "VulkanInfo.hpp"
#include "VulkanInfoConst.hpp"
#include <SDL_vulkan.h>
#include "engine/RenderEngine.hpp"
#include <config/RenderConfig.hpp>

using namespace CubA4::render;

VulkanInfo::VulkanInfo()
{

}

VulkanInfo::~VulkanInfo()
{

}

void VulkanInfo::init(std::shared_ptr<const CubA4::info::IApplicationInfo> info, std::shared_ptr<const CubA4::ICore> core)
{
	info_ = info;
	core_ = core;
	config_ = std::make_shared<config::RenderConfig>(core_->getPaths()->configPath());
	engine_ = std::make_shared<engine::VulkanRenderEngine>(info_, core_, config_);
}

void VulkanInfo::destroy()
{

}

std::string VulkanInfo::getRenderEngineId() const
{
	return RenderEngineId;
}

std::shared_ptr<engine::IRenderEngine> VulkanInfo::getRenderEngine()
{
	return engine_;
}

std::shared_ptr<config::IRenderConfig> VulkanInfo::getRenderConfig() const
{
	return config_;
}

uint32_t VulkanInfo::getSDLWindowFlags() const
{
	return SDL_WINDOW_VULKAN;
}
