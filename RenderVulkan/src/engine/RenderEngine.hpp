#ifndef RENDERVULKAN_RENDERENGINE_HPP
#define RENDERVULKAN_RENDERENGINE_HPP

#include <engine/IRenderEngine.hpp>
#include <vector>
#include <thread>
#include "RenderEngineCore.hpp"

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			class Presentaion;
			class Render;
			class RenderManager;
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
				explicit VulkanRenderEngine(std::shared_ptr<const core::info::IApplicationInfo> info, std::shared_ptr<const core::ICore> core);
				explicit VulkanRenderEngine(const VulkanRenderEngine &) = delete;
				~VulkanRenderEngine();

				void init(std::shared_ptr<const window::IWindow> window) override;
				void destroy() override;

				void setGame(std::shared_ptr<const CubA4::core::game::IGame> game) override;

				void run() override;
				void stop() override;

				std::shared_ptr<IRenderManager> getRenderManager() const override;
			protected:
				void initPresentation();
				void destroyPresentation();

				void initRender();
				void destroyRender();

				void setup();
				void shutdown();

				void loop();
			private:
				std::shared_ptr<Presentaion> presetation_;
				std::shared_ptr<Render> render_;

				std::shared_ptr<RenderManager> renderManager_;
				std::shared_ptr<RenderGameHandler> renderGameHandler_;
				std::shared_ptr<pipeline::RenderChunkCompiler> renderChunkCompiler_;
				std::shared_ptr<pipeline::RenderEnginePipeline> renderEnginePipeline_;

				bool running_;
				std::thread renderLoopThread_;
			};
		}
	}
}

#endif // RENDERVULKAN_RENDERENGINE_HPP
