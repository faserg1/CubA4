#include "./VulkanRenderEngine.hpp"
#include "../vulkan/VulkanInstance.hpp"
#include "../vulkan/VulkanInstanceBuilder.hpp"
#include "../vulkan/addon/VulkanSDLExtension.hpp"
#include "../vulkan/addon/VulkanDebugExtension.hpp"
#include <algorithm>
#include <stdexcept>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

VulkanRenderEngine::VulkanRenderEngine(std::shared_ptr<const CubA4::core::info::IApplicationInfo> info) :
	info_(info), instanceBuilder_(std::make_shared<VulkanInstanceBuilder>(info_))
{
	
}

VulkanRenderEngine::~VulkanRenderEngine()
{
	
}

void VulkanRenderEngine::init(std::shared_ptr<CubA4::window::IWindow> window)
{
	if (instance_)
		throw std::runtime_error("Already initialized");
	auto vkSDLExt = std::make_shared<VulkanSDLExtension>(window);
	instanceBuilder_->addExtension(*vkSDLExt);
	addons_.push_back(vkSDLExt);
	instance_ = instanceBuilder_->build();
	std::for_each(addons_.begin(), addons_.end(), [this](std::shared_ptr<VulkanInstanceAddon> addon) {addon->init(instance_); });
}

void VulkanRenderEngine::destroy()
{
	if (!instance_)
		throw std::runtime_error("Not initialized");
	std::for_each(addons_.begin(), addons_.end(), [this](std::shared_ptr<VulkanInstanceAddon> addon) {addon->destroy(instance_); });
	addons_.clear();
	instanceBuilder_->destroy(instance_);
	instance_.reset();
}