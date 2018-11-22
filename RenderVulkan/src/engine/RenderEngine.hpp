#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

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
				void initSwapchain();
				void rebuildSwapchain();
				void destroySwapchain();

				void initPresentation();
				void destroyPresentation();

				void initRender();
				void destroyRender();

				void setup();
				void unload();

				void loop();
			private:
				std::shared_ptr<vulkan::SwapchainBuilder> swapchainBuilder_;
				std::shared_ptr<const vulkan::Swapchain> swapchain_;

				std::shared_ptr<Presentaion> presetation_;
				std::shared_ptr<Render> render_;

				std::shared_ptr<RenderManager> renderManager_;
				std::shared_ptr<RenderGameHandler> renderGameHandler_;

				bool running_;
				std::thread renderLoopThread_;
			};
		}
	}
}

#endif // RENDERENGINE_HPP
