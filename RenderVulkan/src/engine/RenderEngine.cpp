#include "./RenderEngine.hpp" 

#include <ICore.hpp>
#include <config/IFilePaths.hpp>
#include <logging/ILogger.hpp>

#include "../config/RenderConfig.hpp" 

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

#include "../vulkan/Swapchain.hpp" 
#include "../vulkan/SwapchainBuilder.hpp" 

#include "./Presentaion.hpp" 
#include "./Render.hpp" 

#include <algorithm>
#include <stdexcept>
using namespace CubA4::core::logging;
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

constexpr char *loggerTag = "ENGINE";

RenderEngine::RenderEngine(
	std::shared_ptr<const CubA4::core::info::IApplicationInfo> info,
	std::shared_ptr<const CubA4::core::ICore> core) :
	info_(info), core_(core), logger_(core->getLogger())
{
	config_ = std::make_shared<config::RenderConfig>(core->getPaths()->configPath());
}

RenderEngine::~RenderEngine()
{
	
}

void RenderEngine::init(std::shared_ptr<CubA4::window::IWindow> window)
{
	window_ = window;
	initInstance();
	initDevice();
	initSwapchain();
	initPresentation();
	initRender();
	setup();
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Render engine initialized.");
}

void RenderEngine::destroy()
{
	destroyRender();
	destroyPresentation();
	destroySwapchain();
	destroyDevice();
	destroyInstance();
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Render engine destroyed.");
}

void RenderEngine::initInstance()
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
	
	auto vkDebugExt = std::make_shared<DebugExtension>(logger_);
	addExt(vkDebugExt);

	auto vkStdLayer = std::make_shared<StandardValidationLayer>();
	addLayer(vkStdLayer);

	instance_ = instanceBuilder_->build();
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<InstanceAddon> addon) {addon->init(instance_); });

	surface_ = vkSDLExt->getSurface();
}

void RenderEngine::destroyInstance()
{
	if (!instance_)
		throw std::runtime_error("Not initialized");
	std::for_each(instanceAddons_.begin(), instanceAddons_.end(),
		[this](std::shared_ptr<InstanceAddon> addon) {addon->destroy(instance_); });
	instanceAddons_.clear();
	instanceBuilder_->destroy(instance_);
	instance_.reset();
}

void RenderEngine::initDevice()
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

void RenderEngine::destroyDevice()
{
	std::for_each(deviceAddons_.begin(), deviceAddons_.end(),
		[this](std::shared_ptr<DeviceAddon> addon) {addon->destroy(device_); });
	deviceAddons_.clear();
	deviceBuilder_->destroy(device_);
	device_.reset();
}


void RenderEngine::initSwapchain()
{
	if (!swapchainBuilder_)
		swapchainBuilder_ = std::make_shared<SwapchainBuilder>(device_, surface_, config_);
	swapchain_ = swapchainBuilder_->build();
}

void RenderEngine::rebuildSwapchain()
{

}

void RenderEngine::destroySwapchain()
{
	swapchainBuilder_->destroy(swapchain_);
	swapchain_.reset();
}


void RenderEngine::initPresentation()
{
	if (!presetation_)
		presetation_ = std::make_shared<Presentaion>(device_, swapchain_);

}

void RenderEngine::destroyPresentation()
{
	presetation_.reset();
}

void RenderEngine::initRender()
{

}

void RenderEngine::destroyRender()
{
	render_.reset();
}

void RenderEngine::setup()
{
	//TODO: [OOKAMI] настройка Presentation & Render
}

void RenderEngine::run()
{
	//TODO: [OOKAMI] запуск основного рендер потока
}