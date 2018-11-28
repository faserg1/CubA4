#include "./RenderEngineCore.hpp"
#include "../config/RenderConfig.hpp"

#include <ICore.hpp>
#include <config/IFilePaths.hpp>
#include <logging/ILogger.hpp>

#include "../vulkan/Instance.hpp"
#include "../vulkan/InstanceBuilder.hpp"
#include "../vulkan/addon/InstanceLayer.hpp"
#include "../vulkan/addon/InstanceExtension.hpp"

#include "../vulkan/Device.hpp"
#include "../vulkan/DeviceBuilder.hpp"
#include "../vulkan/addon/DeviceLayer.hpp"
#include "../vulkan/addon/DeviceExtension.hpp"

#include "../vulkan/addon/SDLExtension.hpp"
#include "../vulkan/addon/DebugExtension.hpp"
#include "../vulkan/addon/SwapchainExtension.hpp"
#include "../vulkan/addon/StandardValidationLayer.hpp"

using namespace CubA4::core::logging;
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

RenderEngineCore::RenderEngineCore(std::shared_ptr<const CubA4::core::info::IApplicationInfo> info, std::shared_ptr<const CubA4::core::ICore> core) :
	info_(info), core_(core), logger_(core->getLogger())
{
	config_ = std::make_shared<config::RenderConfig>(core->getPaths()->configPath());
}

RenderEngineCore::~RenderEngineCore()
{
	
}

void RenderEngineCore::initCore(std::shared_ptr<const CubA4::window::IWindow> window)
{
	window_ = window;
	initInstance();
	initDevice();
}

void RenderEngineCore::destroyCore()
{
	destroyDevice();
	destroyInstance();
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

void RenderEngineCore::initInstance()
{
	if (!instanceBuilder_)
		instanceBuilder_ = std::make_shared<InstanceBuilder>(info_);
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

#ifdef _DEBUG
	auto vkDebugExt = std::make_shared<DebugExtension>(logger_);
	addExt(vkDebugExt);

	auto vkStdLayer = std::make_shared<StandardValidationLayer>();
	addLayer(vkStdLayer);
#endif

	instance_ = instanceBuilder_->build();
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<InstanceAddon> addon) {addon->init(instance_); });
	surface_ = vkSDLExt->getSurface();
}

void RenderEngineCore::destroyInstance()
{
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
	addExt(vkSwapChainExt);
	device_ = deviceBuilder_->build();
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<DeviceAddon> addon) {addon->init(device_); });
}

void RenderEngineCore::destroyDevice()
{
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<DeviceAddon> addon) {addon->destroy(device_); });
	deviceAddons_.clear();
	deviceBuilder_->destroy(device_);
	device_.reset();
}
