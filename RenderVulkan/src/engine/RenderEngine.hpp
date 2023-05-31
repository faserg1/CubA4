#pragma once

#include <engine/IRenderEngine.hpp>
#include <vector>
#include <thread>
#include <atomic>
#include <engine/RenderEngineCore.hpp>

namespace CubA4::render::engine
{
	class Presentaion;
	class Render;
	class RenderManager;
	class RenderPassManager;
	class FramebufferManager;
	class RenderGameHandler;

	namespace pipeline
	{
		class RenderChunkCompiler;
		class RenderEnginePipeline;
	}

	class VulkanRenderEngine :
		public virtual IRenderEngine,
		public RenderEngineCore
	{
	public:
		explicit VulkanRenderEngine(std::shared_ptr<const info::IApplicationInfo> info, std::shared_ptr<const ICore> core, std::shared_ptr<config::IRenderConfig> config);
		explicit VulkanRenderEngine(const VulkanRenderEngine &) = delete;
		~VulkanRenderEngine();

		void init(std::shared_ptr<const window::IWindow> window) override;
		void destroy() override;

		void setGame(std::shared_ptr<const CubA4::game::IGame> game) override;
		void onWindowResized() override;

		void run() override;
		void stop() override;

		std::shared_ptr<IRenderManager> getRenderManager() const override;
	protected:
		void initManagers();
		void destroyManagers();

		void initPresentation();
		void destroyPresentation();

		void initRender();
		void destroyRender();

		void setup();
		void shutdown();

		void loop();

		void inFrameRebuild();
	private:
		std::shared_ptr<Presentaion> presetation_;
		std::shared_ptr<Render> render_;

		std::shared_ptr<RenderGameHandler> renderGameHandler_;
		std::shared_ptr<pipeline::RenderEnginePipeline> renderEnginePipeline_;
		
		std::shared_ptr<RenderManager> renderManager_;
		std::shared_ptr<RenderPassManager> renderPassManager_;
		std::shared_ptr<FramebufferManager> framebufferManager_;

		bool running_;
		std::atomic_bool rebuildSwapchain_;
		std::thread renderLoopThread_;
	};
}
