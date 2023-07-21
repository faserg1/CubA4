#include "./RenderEngine.hpp"

#include <logging/ILogger.hpp>

#include <engine/Presentaion.hpp>
#include <engine/Render.hpp>
#include <engine/RenderUI.hpp>

#include <engine/framebuffer/MainFramebufferManager.hpp>

#include "./RenderManager.hpp"
#include "./RenderGameHandler.hpp"
#include "./pipeline/RenderChunkCompiler.hpp"
#include "./pipeline/RenderEnginePipeline.hpp"

#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <limits>
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

uint16_t VulkanRenderEngine::getCurrentFPS() const
{
	return fps_;
}

void VulkanRenderEngine::initManagers()
{
	renderPassManager_ = std::make_shared<RenderPassManager>(getDevice(), getConfig());
	framebufferManager_ = std::make_shared<MainFramebufferManager>(getDevice(), getConfig());
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
	renderUi_.reset();
	render_.reset();
}

void VulkanRenderEngine::setup()
{
	renderPassManager_->createRenderPasses(getSwapchain()->getFormat());
	renderManager_->onRenderPassCreated();

	renderEnginePipeline_ = std::make_shared<pipeline::RenderEnginePipeline>(core_, getDevice(), renderPassManager_, renderManager_);

	framebufferManager_->setRenderPass(renderPassManager_->getMainRenderPass());

	handleSwapChainChanged();

	renderManager_->setup();

	render_->setup(renderEnginePipeline_->getWorldPipeline());

	renderGameHandler_ = std::make_shared<RenderGameHandler>(renderEnginePipeline_->getWorldPipeline());

	mainPipelines_.push_back(this);
	mainPipelines_.push_back(renderManager_->getDebug().get());
	mainPipelines_.push_back(renderUi_.get());
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
	auto start = clock();
	uint16_t frame = 0;
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

		renderManager_->getWorldManager()->onFrameUpdate();

		std::shared_ptr<const CubA4::render::vulkan::Semaphore> renderDoneSemaphore = acquireSemaphore;

		for (auto &step : mainPipelines_)
		{
			auto doneSemaphore = step->render(imgIndex, renderDoneSemaphore);
			if (doneSemaphore)
				renderDoneSemaphore = doneSemaphore;
		}

		//renderManager_->getDebug()->record(framebuffer, imgIndex);
		
		if (renderDoneSemaphore && renderDoneSemaphore != acquireSemaphore)
			presetation_->send(currentSwapchain, imgIndex, { renderDoneSemaphore });
			
		
		frame++;
		auto currentClock = clock();
		if (currentClock > start + CLOCKS_PER_SEC)
		{
			fps_ = frame;
			frame = 0;
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
	handleSwapChainChanged();
}

void VulkanRenderEngine::handleSwapChainChanged()
{
	framebufferManager_->onSwapchainUpdate(getSwapchain());

	
	const auto mainAttachments = framebufferManager_->getAttachmentsCount();
	const auto mainImages = framebufferManager_->getImageCount();
	const auto maxIdx = std::numeric_limits<uint32_t>::max();
	auto depthIdx = std::numeric_limits<uint32_t>::max();

	std::vector<VkImage> depths(mainImages);

	for (uint32_t imageIdx = 0; imageIdx < mainImages; imageIdx++)
	{
		if (depthIdx == maxIdx)
		{
			for (uint32_t aIdx = 0; aIdx < mainAttachments; aIdx++)
			{
				const auto &attachment = framebufferManager_->get(imageIdx)->getFrameBufferImage(aIdx);
				if (attachment.getAspectFlags() == VK_IMAGE_ASPECT_DEPTH_BIT)
				{
					depthIdx = aIdx;
					break;
				}
			}
		}
		const auto &attachment = framebufferManager_->get(imageIdx)->getFrameBufferImage(depthIdx);
		depths[imageIdx] = attachment.getImage();
	}

	renderManager_->getUIManager()->swapchainChanged(getSwapchain());
	renderManager_->getDebug()->swapchainChanged(getSwapchain(), std::move(depths));

	// TODO: [OOKAMI] Call UI and pass VkImageInfo from framebuffers

	auto [width, height] = getSwapchain()->getResolution();
	auto data = pipeline::RenderFramebufferData {
		.width = width,
		.height = height
	};
	
	renderManager_->getWorldManager()->onViewportUpdate(width, height);
	renderEnginePipeline_->onFramebufferUpdated(data);
}

std::shared_ptr<const CubA4::render::vulkan::Semaphore> VulkanRenderEngine::render(
	uint32_t imgIndex, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore)
{
	auto framebuffer = framebufferManager_->onAcquire(imgIndex);
	
	render_->record(framebuffer);

	return render_->send(framebuffer, awaitSemaphore);
}