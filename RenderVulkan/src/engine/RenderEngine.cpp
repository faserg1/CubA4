#include "./RenderEngine.hpp"

#include <logging/ILogger.hpp>

#include "./Presentaion.hpp"
#include "./Render.hpp"

#include "./RenderManager.hpp"
#include "./RenderGameHandler.hpp"
#include "./pipeline/RenderChunkCompiler.hpp"
#include "./pipeline/RenderEnginePipeline.hpp"

#include <algorithm>
#include <stdexcept>
#include <ctime>
using namespace CubA4::core::logging;
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

constexpr const char *loggerTag = "ENGINE";

VulkanRenderEngine::VulkanRenderEngine(
	std::shared_ptr<const CubA4::core::info::IApplicationInfo> info,
	std::shared_ptr<const CubA4::core::ICore> core) :
	RenderEngineCore(info, core),
	running_(false)
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
	destroyCore();	
	logger_->log(LogSourceSystem::Render, loggerTag, LogLevel::Info, "Render engine destroyed.");
}


std::shared_ptr<IRenderManager> VulkanRenderEngine::getRenderManager() const
{
	return renderManager_;
}

void VulkanRenderEngine::setGame(std::shared_ptr<const CubA4::core::game::IGame> game)
{
	renderGameHandler_->setGame(game);
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


void VulkanRenderEngine::initPresentation()
{
	if (!presetation_)
		presetation_ = std::make_shared<Presentaion>(getDevice(), getSwapchain());

}

void VulkanRenderEngine::destroyPresentation()
{
	presetation_.reset();
}


void VulkanRenderEngine::initRender()
{
	if (!render_)
		render_ = std::make_shared<Render>(getDevice(), getSwapchain());
}

void VulkanRenderEngine::destroyRender()
{
	render_.reset();
}


void VulkanRenderEngine::setup()
{
	// Создание компонентов
	renderManager_ = std::make_shared<RenderManager>(getDevice(), render_);
	renderChunkCompiler_ = std::make_shared<pipeline::RenderChunkCompiler>(getDevice(), render_->getRenderPass(), renderManager_->getWorldManager());
	renderEnginePipeline_ = std::make_shared<pipeline::RenderEnginePipeline>(renderChunkCompiler_);
	
	render_->setup(renderEnginePipeline_);

	renderGameHandler_ = std::make_shared<RenderGameHandler>(renderEnginePipeline_);
}

void VulkanRenderEngine::shutdown()
{
	// Разрушение компонентов
	renderGameHandler_.reset();

	if (render_)
		render_->shutdown();

	renderEnginePipeline_.reset();
	renderChunkCompiler_.reset();
	renderManager_.reset();
}

void VulkanRenderEngine::loop()
{
	auto acquireSemaphore = presetation_->getAcquireSignalSemaphore();
	unsigned short fps = 0;
	auto start = clock();
	while (running_)
	{
		auto imgIndex = presetation_->acquire();
		if (imgIndex == UINT32_MAX)
			continue;
		render_->record(imgIndex);
		auto renderDoneSemaphore = render_->send(imgIndex, acquireSemaphore);

		if (renderDoneSemaphore)
			presetation_->send(imgIndex, { renderDoneSemaphore });
		
		
		fps++;
		auto currentClock = clock();
		if (currentClock > start + CLOCKS_PER_SEC)
		{
			logger_->log(LogSourceSystem::Render, "RENDERENGINE", LogLevel::Debug, "Current framerate: " + std::to_string(fps));
			fps = 0;
			start = currentClock;
		}
	}
}
