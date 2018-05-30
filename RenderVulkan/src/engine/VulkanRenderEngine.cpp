#include "./VulkanRenderEngine.hpp"

#include "../vulkan/VulkanInstance.hpp"
#include "../vulkan/VulkanInstanceBuilder.hpp"
#include "../vulkan/addon/VulkanInstanceLayer.hpp"
#include "../vulkan/addon/VulkanInstanceExtension.hpp"

#include "../vulkan/VulkanDevice.hpp"
#include "../vulkan/VulkanDeviceBuilder.hpp"
#include "../vulkan/addon/VulkanDeviceLayer.hpp"
#include "../vulkan/addon/VulkanDeviceExtension.hpp"

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
	info_(info), logger_(logger)
{
	
}

VulkanRenderEngine::~VulkanRenderEngine()
{
	
}

void VulkanRenderEngine::init(std::shared_ptr<CubA4::window::IWindow> window)
{
	window_ = window;
	initInstance();
	initDevice();
}

void VulkanRenderEngine::destroy()
{
	destroyDevice();
	destroyInstance();
}

void VulkanRenderEngine::initInstance()
{
	instanceBuilder_ = std::make_shared<VulkanInstanceBuilder>(info_);
	if (instance_)
		throw std::runtime_error("Already initialized");
	auto addExt = [=](std::shared_ptr<VulkanInstanceExtension> ext)
	{
		instanceBuilder_->addExtension(*ext);
		instanceAddons_.push_back(ext);
	};
	auto addLayer = [=](std::shared_ptr<VulkanInstanceLayer> layer)
	{
		instanceBuilder_->addLayer(*layer);
		instanceAddons_.push_back(layer);
	};


	std::shared_ptr<VulkanSDLExtension> vkSDLExt;
	if (auto window = window_.lock())
	{
		vkSDLExt = std::make_shared<VulkanSDLExtension>(window);
		addExt(vkSDLExt);
	}
	else
		throw std::runtime_error("Window destroyed! Cannot init surface!");
	
	auto vkDebugExt = std::make_shared<VulkanDebugExtension>(logger_);
	addExt(vkDebugExt);

	auto vkStdLayer = std::make_shared<VulkanStandardValidationLayer>();
	addLayer(vkStdLayer);

	instance_ = instanceBuilder_->build();
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<VulkanInstanceAddon> addon) {addon->init(instance_); });

	surface_ = vkSDLExt->getSurface();
}

void VulkanRenderEngine::destroyInstance()
{
	if (!instance_)
		throw std::runtime_error("Not initialized");
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<VulkanInstanceAddon> addon) {addon->destroy(instance_); });
	instanceAddons_.clear();
	instanceBuilder_->destroy(instance_);
	instance_.reset();
}

void VulkanRenderEngine::initDevice()
{
	deviceBuilder_ = std::make_shared<VulkanDeviceBuilder>(instance_, surface_);
	auto addExt = [=](std::shared_ptr<VulkanDeviceExtension> ext)
	{
		deviceBuilder_->addExtension(*ext);
		deviceAddons_.push_back(ext);
	};
	auto vkSwapChainExt = std::make_shared<VulkanSwapchainExtension>(deviceBuilder_->getPhysicalDevice());
	addExt(vkSwapChainExt);
	device_ = deviceBuilder_->build();
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<VulkanDeviceAddon> addon) {addon->init(device_); });
}

void VulkanRenderEngine::destroyDevice()
{
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<VulkanDeviceAddon> addon) {addon->destroy(device_); });
	deviceAddons_.clear();
	deviceBuilder_->destroy(device_);
	device_.reset();
}