#ifndef RENDERENGINE_HPP
#define RENDERENGINE_HPP

#include <engine/IRenderEngine.hpp>
#include <vector>
#include <thread>

namespace CubA4
{
	namespace core
	{
		class ICore;
		namespace logging
		{
			class ILogger;
		}
		namespace info
		{
			class IApplicationInfo;
		}
	}

	namespace render
	{
		namespace config
		{
			class IRenderConfig;
		}

		namespace vulkan
		{
			class Instance;
			class InstanceBuilder;
			class Device;
			class DeviceBuilder;
			class Surface;
			class Swapchain;
			class SwapchainBuilder;

			namespace addon
			{
				class InstanceAddon;
				class DeviceAddon;
			}
		}

		namespace engine
		{
			class Presentaion;
			class Render;
			class RenderManager;

			class VulkanRenderEngine :
				public virtual IRenderEngine
			{
			public:
				explicit VulkanRenderEngine(std::shared_ptr<const core::info::IApplicationInfo> info, std::shared_ptr<const core::ICore> core);
				explicit VulkanRenderEngine(const VulkanRenderEngine &) = delete;
				~VulkanRenderEngine();

				void init(std::shared_ptr<window::IWindow> window) override;
				void destroy() override;

				void setGame(std::shared_ptr<const CubA4::core::game::IGame> game) override;

				void run() override;
				void stop() override;

				std::shared_ptr<IRenderManager> getRenderManager() const override;
			protected:
				void initInstance();
				void destroyInstance();

				void initDevice();
				void destroyDevice();

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
				std::shared_ptr<const core::info::IApplicationInfo> info_;
				std::shared_ptr<const core::ICore> core_;
				std::shared_ptr<core::logging::ILogger> logger_;
				std::shared_ptr<config::IRenderConfig> config_;

				std::weak_ptr<window::IWindow> window_;
				std::weak_ptr<const vulkan::Surface> surface_;

				std::shared_ptr<vulkan::InstanceBuilder> instanceBuilder_;
				std::shared_ptr<const vulkan::Instance> instance_;
				std::vector<std::shared_ptr<vulkan::addon::InstanceAddon>> instanceAddons_;

				std::shared_ptr<vulkan::DeviceBuilder> deviceBuilder_;
				std::shared_ptr<const vulkan::Device> device_;
				std::vector<std::shared_ptr<vulkan::addon::DeviceAddon>> deviceAddons_;

				std::shared_ptr<vulkan::SwapchainBuilder> swapchainBuilder_;
				std::shared_ptr<const vulkan::Swapchain> swapchain_;

				std::shared_ptr<Presentaion> presetation_;
				std::shared_ptr<Render> render_;

				std::shared_ptr<RenderManager> renderManager_;

				bool running_;
				std::thread renderLoopThread_;
			};
		}
	}
}

#endif // RENDERENGINE_HPP
