#include "./RenderEngine.hpp"

#include <logging/ILogger.hpp>

#include <engine/Presentaion.hpp>
#include <engine/Render.hpp>
#include <engine/RenderUI.hpp>

#include "./RenderManager.hpp"
#include "./RenderGameHandler.hpp"
#include "./pipeline/RenderChunkCompiler.hpp"
#include "./pipeline/RenderEnginePipeline.hpp"

#include <algorithm>
#include <stdexcept>
#include <ctime>
using namespace CubA4::logging;
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

constexpr const char *loggerTag = "ENGINE";

VulkanRenderEngine::VulkanRenderEngine(
	std::shared_ptr<const CubA4::info::IApplicationInfo> info,
	std::shared_ptr<const CubA4::ICore> core,
	std::shared_ptr<config::IRenderConfig> config) :
	RenderEngineCore(info, core, config),
	running_(false),
	rebuildSwapchain_(false)
{
}

VulkanRenderEngine::~VulkanRenderEngine()
{
	stop();
	destroy();
}

void VulkanRenderEngine::init(std::shared_ptr<const CubA4::window::IWindow> window)
{
	initCore(window);
	initManagers();
	initPresentation();
	initRender();
	setup();
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Render engine initialized.");
}

void VulkanRenderEngine::destroy()
{
	shutdown();
	destroyRender();
	destroyPresentation();
	destroyManagers();
	destroyCore();	
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Render engine destroyed.");
}


std::shared_ptr<IRenderManager> VulkanRenderEngine::getRenderManager() const
{
	return renderManager_;
}

void VulkanRenderEngine::setGame(std::shared_ptr<const CubA4::game::IGame> game)
{
	renderGameHandler_->setGame(game);
}

void VulkanRenderEngine::onWindowResized()
{
	rebuildSwapchain_.store(true);
}

void VulkanRenderEngine::run()
{
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Starting.");
	running_ = true;
	renderLoopThread_ = std::thread(&VulkanRenderEngine::loop, this);
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Started.");
}

void VulkanRenderEngine::stop()
{
	if (!running_)
		return;
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Stopping.");
	running_ = false;
	if (renderLoopThread_.joinable())
		renderLoopThread_.join();
	waitDeviceIdle();
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Stoped.");
}

void VulkanRenderEngine::initManagers()
{
	renderPassManager_ = std::make_shared<RenderPassManager>(getDevice(), getConfig());
	framebufferManager_ = std::make_shared<FramebufferManager>(getDevice(), getConfig());
	renderManager_ = std::make_shared<RenderManager>(getInstance(), getDevice(), core_, renderPassManager_, getConfig());
}

void VulkanRenderEngine::destroyManagers()
{
	renderManager_.reset();
	framebufferManager_.reset();
	renderPassManager_.reset();
}

void VulkanRenderEngine::initPresentation()
{
	if (!presetation_)
		presetation_ = std::make_shared<Presentaion>(getDevice());
}

void VulkanRenderEngine::destroyPresentation()
{
	presetation_.reset();
}

void VulkanRenderEngine::initRender()
{
	if (!render_)
		render_ = std::make_shared<Render>(getDevice(), renderPassManager_, framebufferManager_, getConfig());
	if (!renderUi_)
		renderUi_ = std::make_shared<RenderUI>(getDevice(), framebufferManager_, renderManager_);
}

void VulkanRenderEngine::destroyRender()
{
	render_.reset();
}

void VulkanRenderEngine::setup()
{
	// Создание компонентов
	auto [width, height] = getSwapchain()->getResolution();
	auto data = pipeline::RenderFramebufferData {
		.width = width,
		.height = height
	};
	renderManager_->getWorldManager()->onViewportUpdate(width, height);
	renderManager_->getUIManager()->swapchainChanged(getSwapchain());

	renderPassManager_->createRenderPasses(getSwapchain()->getFormat());
	framebufferManager_->onSwapchainUpdate(getSwapchain(), renderPassManager_->getMainRenderPass());

	// TODO: [OOKAMI] Call UI and pass VkImageInfo from framebuffers
	renderEnginePipeline_ = std::make_shared<pipeline::RenderEnginePipeline>(core_, getDevice(), renderPassManager_, renderManager_);
	renderEnginePipeline_->onFramebufferUpdated(data);

	render_->setup(renderEnginePipeline_->getWorldPipeline());

	renderGameHandler_ = std::make_shared<RenderGameHandler>(renderEnginePipeline_->getWorldPipeline());
}

void VulkanRenderEngine::shutdown()
{
	// Разрушение компонентов
	renderGameHandler_.reset();

	if (render_)
		render_->shutdown();

	renderEnginePipeline_.reset();
}

void VulkanRenderEngine::loop()
{
	auto acquireSemaphore = presetation_->getAcquireSignalSemaphore();
	unsigned short fps = 0;
	auto start = clock();
	while (running_)
	{
		inFrameRebuild();
		auto currentSwapchain = getSwapchain();
		auto imgIndex = presetation_->acquire(currentSwapchain);
		if (imgIndex == UINT32_MAX)
		{
			render_->onAcquireFailed(acquireSemaphore);
			framebufferManager_->onAcquireFailed();
			continue;
		}
		// Take framebuffer and work with him
		// take framebuffer from framebufferManager_?
		// auto framebuffer = render_->onAcquire(imgIndex);
		auto framebuffer = framebufferManager_->onAcquire(imgIndex);
		renderManager_->getWorldManager()->onFrameUpdate();
		render_->record(framebuffer);
		auto renderDoneSemaphore = render_->send(framebuffer, acquireSemaphore);
		

		if (renderDoneSemaphore)
		{
			auto uiRenderDoneSemaphore = renderUi_->render(imgIndex, renderDoneSemaphore);
			if (uiRenderDoneSemaphore)
				renderDoneSemaphore = uiRenderDoneSemaphore;
		}
			
			
		if (renderDoneSemaphore)
			presetation_->send(currentSwapchain, imgIndex, { renderDoneSemaphore });
			
		
		fps++;
		auto currentClock = clock();
		if (currentClock > start + CLOCKS_PER_SEC)
		{
			logger_->log(LogSourceSystem::Render, "RENDERENGINE", LogLevel::Debug, "Current framerate: " + std::to_string(fps));
			fps = 0;
			start = currentClock;
		}
		std::this_thread::yield();
	}
}


void VulkanRenderEngine::inFrameRebuild()
{
	if (!rebuildSwapchain_.load())
		return;
	rebuildSwapchain_.store(false);
	rebuildSwapChain();
	framebufferManager_->onSwapchainUpdate(getSwapchain(), renderPassManager_->getMainRenderPass());
	renderManager_->getUIManager()->swapchainChanged(getSwapchain());

	// TODO: [OOKAMI] Call UI and pass VkImageInfo from framebuffers

	auto [width, height] = getSwapchain()->getResolution();
	auto data = pipeline::RenderFramebufferData {
		.width = width,
		.height = height
	};
	
	renderManager_->getWorldManager()->onViewportUpdate(width, height);
	renderEnginePipeline_->onFramebufferUpdated(data);
}