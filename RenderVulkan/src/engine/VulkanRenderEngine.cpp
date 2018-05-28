#include "./VulkanRenderEngine.hpp"
#include "../vulkan/VulkanInstance.hpp"
#include "../vulkan/VulkanInstanceBuilder.hpp"
#include "../vulkan/addon/VulkanInstanceLayer.hpp"
#include "../vulkan/addon/VulkanInstanceExtension.hpp"

#include "../vulkan/addon/VulkanSDLExtension.hpp"
#include "../vulkan/addon/VulkanDebugExtension.hpp"
#include "../vulkan/addon/VulkanSwapchainExtension.hpp"
#include "../vulkan/addon/VulkanStandardValidationLayer.hpp"

#include <algorithm>
#include <stdexcept>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

VulkanRenderEngine::VulkanRenderEngine(std::shared_ptr<const CubA4::core::info::IApplicationInfo> info, std::shared_ptr<CubA4::core::logging::ILogger> logger) :
	info_(info), logger_(logger), instanceBuilder_(std::make_shared<VulkanInstanceBuilder>(info_))
{
	
}

VulkanRenderEngine::~VulkanRenderEngine()
{
	
}

void VulkanRenderEngine::init(std::shared_ptr<CubA4::window::IWindow> window)
{
	if (instance_)
		throw std::runtime_error("Already initialized");
	auto addExt = [=](std::shared_ptr<VulkanExtension> ext)
	{
		instanceBuilder_->addExtension(*ext);
		addons_.push_back(ext);
	};
	auto addLayer = [=](std::shared_ptr<VulkanInstanceLayer> layer)
	{
		instanceBuilder_->addLayer(*layer);
		addons_.push_back(layer);
	};

	auto vkSDLExt = std::make_shared<VulkanSDLExtension>(window);
	addExt(vkSDLExt);

	auto vkDebugExt = std::make_shared<VulkanDebugExtension>(logger_);
	addExt(vkDebugExt);

	auto vkSwapChainExt = std::make_shared<VulkanSwapchainExtension>();
	addExt(vkSwapChainExt);

	auto vkStdLayer = std::make_shared<VulkanStandardValidationLayer>();
	addLayer(vkStdLayer);

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