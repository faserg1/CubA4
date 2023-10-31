#include "./RenderEngineCore.hpp"
#include "../config/RenderConfig.hpp"

#include <ICore.hpp>
#include <config/IFilePaths.hpp>
#include <logging/ILogger.hpp>

#include <vulkan/vulkan.h>
#include <algorithm>

#include <vulkan/Instance.hpp>
#include <vulkan/InstanceBuilder.hpp>
#include <vulkan/addon/InstanceLayer.hpp>
#include <vulkan/addon/InstanceExtension.hpp>

#include <vulkan/Device.hpp>
#include <vulkan/DeviceBuilder.hpp>
#include <vulkan/addon/DeviceLayer.hpp>
#include <vulkan/addon/DeviceExtension.hpp>

#include <vulkan/addon/SDLExtension.hpp>
#include <vulkan/addon/DebugExtension.hpp>
#include <vulkan/addon/SwapchainExtension.hpp>
#include <vulkan/addon/Synchronization2Extension.hpp>
#include <vulkan/addon/DepthStensilResolveExtension.hpp>
#include <vulkan/addon/StandardValidationLayer.hpp>
#include <vulkan/addon/RenderDocCaptureLayer.hpp>

#include <vulkan/Swapchain.hpp>
#include <vulkan/SwapchainBuilder.hpp>

using namespace CubA4::logging;
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

constexpr const char *loggerTag = "ENGINE_CORE";

RenderEngineCore::RenderEngineCore(std::shared_ptr<const CubA4::info::IApplicationInfo> info, std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<config::IRenderConfig> config) :
	info_(info), core_(core), logger_(core->getLogger()), config_(config)
{
	
}

RenderEngineCore::~RenderEngineCore()
{
	destroyCore();
}

void RenderEngineCore::initCore(std::shared_ptr<const CubA4::window::IWindow> window)
{
	window_ = window;
	initInstance();
	initDevice();
	initSwapchain();
}

void RenderEngineCore::destroyCore()
{
	waitDeviceIdle();
	destroySwapchain();
	destroyDevice();
	destroyInstance();
}

void RenderEngineCore::rebuildSwapChain()
{
	swapchain_ = swapchainBuilder_->build(swapchain_);
}

std::shared_ptr<const CubA4::render::config::IRenderConfig> RenderEngineCore::getConfig() const
{
	return config_;
}

std::shared_ptr<const Instance> RenderEngineCore::getInstance() const
{
	return instance_;
}

std::shared_ptr<const Device> RenderEngineCore::getDevice() const
{
	return device_;
}

std::weak_ptr<const Surface> RenderEngineCore::getSurface() const
{
	return surface_;
}

std::shared_ptr<const Swapchain> RenderEngineCore::getSwapchain() const
{
	return swapchain_;
}

void RenderEngineCore::waitDeviceIdle() const
{
	if (!device_)
		return;
	auto waitResult = vkDeviceWaitIdle(device_->getDevice());
	if (waitResult != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions
	}
}

void RenderEngineCore::initInstance()
{
	if (!instanceBuilder_)
		instanceBuilder_ = std::make_shared<InstanceBuilder>(core_->getLogger(), info_);
	if (instance_)
		throw std::runtime_error("Already initialized");
	auto addExt = [=](std::shared_ptr<InstanceExtension> ext)
	{
		instanceBuilder_->addExtension(*ext);
		instanceAddons_.push_back(ext);
	};
	auto addLayer = [=](std::shared_ptr<InstanceLayer> layer)
	{
		instanceBuilder_->addLayer(*layer);
		instanceAddons_.push_back(layer);
	};

	std::shared_ptr<SDLExtension> vkSDLExt;
	if (auto window = window_.lock())
	{
		vkSDLExt = std::make_shared<SDLExtension>(window);
		addExt(vkSDLExt);
	}
	else
		throw std::runtime_error("Window destroyed! Cannot init surface!");

#if defined(_DEBUG) || defined(CUBA4_DEBUG)
	auto vkDebugExt = std::make_shared<DebugExtension>(logger_, config_);
	addExt(vkDebugExt);

	auto vkStdLayer = std::make_shared<StandardValidationLayer>();
	addLayer(vkStdLayer);

	auto renderDocCaptureLayer = std::make_shared<RenderDocCaptureLayer>();
	//addLayer(renderDocCaptureLayer);
#endif

	instance_ = instanceBuilder_->build();
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<InstanceAddon> addon) {addon->init(instance_); });
	surface_ = vkSDLExt->createSurface();
}

void RenderEngineCore::destroyInstance()
{
	if (!instance_)
		return;
	surface_.reset();
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<InstanceAddon> addon) {addon->destroy(instance_); });
	instanceAddons_.clear();
	instanceBuilder_->destroy(instance_);
	instance_.reset();
}


void RenderEngineCore::initDevice()
{
	if (!deviceBuilder_)
		deviceBuilder_ = std::make_shared<DeviceBuilder>(instance_, surface_);
	auto addExt = [=](std::shared_ptr<DeviceExtension> ext)
	{
		deviceBuilder_->addExtension(*ext);
		deviceAddons_.push_back(ext);
	};
	auto vkSwapChainExt = std::make_shared<SwapchainExtension>(deviceBuilder_->getPhysicalDevice());
	//auto vkSync2Ext = std::make_shared<Synchronization2Extension>(deviceBuilder_->getPhysicalDevice());
	auto vkDepthStensilResolveExt = std::make_shared<DepthStensilResolveExtension>(deviceBuilder_->getPhysicalDevice());
	addExt(vkSwapChainExt);
	//addExt(vkSync2Ext);
	addExt(vkDepthStensilResolveExt);
	device_ = deviceBuilder_->build();
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<DeviceAddon> addon) {addon->init(device_); });
}

void RenderEngineCore::destroyDevice()
{
	if (!device_)
		return;
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<DeviceAddon> addon) {addon->destroy(device_); });
	deviceAddons_.clear();
	deviceBuilder_->destroy(device_);
	device_.reset();
}

void RenderEngineCore::initSwapchain()
{
	if (!swapchainBuilder_)
		swapchainBuilder_ = std::make_shared<SwapchainBuilder>(getDevice(), getSurface(), config_);
	swapchain_ = swapchainBuilder_->build();
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Swapchain builded.");
}

void RenderEngineCore::destroySwapchain()
{
	if (!swapchain_)
		return;
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Destroing swapchain.");
	swapchainBuilder_->destroy(swapchain_);
	swapchain_.reset();
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Swapchain destroyed.");
}