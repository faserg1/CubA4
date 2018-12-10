#ifndef RENDERVULKAN_RENDERENGINECORE_HPP
#define RENDERVULKAN_RENDERENGINECORE_HPP

#include <memory>
#include <vector>

namespace CubA4
{
	namespace window
	{
		class IWindow;
	}

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
			class RenderEngineCore
			{
			public:
			protected:
				explicit RenderEngineCore(std::shared_ptr<const CubA4::core::info::IApplicationInfo> info, std::shared_ptr<const CubA4::core::ICore> core);
				explicit RenderEngineCore(const RenderEngineCore &) = delete;
				~RenderEngineCore();

				void initCore(std::shared_ptr<const CubA4::window::IWindow> window);
				void destroyCore();

				std::shared_ptr<const CubA4::render::config::IRenderConfig> getConfig() const;
				std::shared_ptr<const vulkan::Instance> getInstance() const;
				std::shared_ptr<const vulkan::Device> getDevice() const;
				std::weak_ptr<const vulkan::Surface> getSurface() const;
				std::shared_ptr<const vulkan::Swapchain> getSwapchain() const;

				void waitDeviceIdle() const;
			protected:
				const std::shared_ptr<const CubA4::core::info::IApplicationInfo> info_;
				const std::shared_ptr<const CubA4::core::ICore> core_;
				const std::shared_ptr<CubA4::core::logging::ILogger> logger_;
			private:
				std::shared_ptr<CubA4::render::config::IRenderConfig> config_;

				std::weak_ptr<const CubA4::window::IWindow> window_;
				std::weak_ptr<const vulkan::Surface> surface_;

				std::shared_ptr<vulkan::InstanceBuilder> instanceBuilder_;
				std::shared_ptr<const vulkan::Instance> instance_;
				std::vector<std::shared_ptr<vulkan::addon::InstanceAddon>> instanceAddons_;

				std::shared_ptr<vulkan::DeviceBuilder> deviceBuilder_;
				std::shared_ptr<const vulkan::Device> device_;
				std::vector<std::shared_ptr<vulkan::addon::DeviceAddon>> deviceAddons_;

				std::shared_ptr<vulkan::SwapchainBuilder> swapchainBuilder_;
				std::shared_ptr<const vulkan::Swapchain> swapchain_;
			private:
				void initInstance();
				void destroyInstance();

				void initDevice();
				void destroyDevice();

				void initSwapchain();
				void rebuildSwapchain();
				void destroySwapchain();
			};
		}
	}
}

#endif // RENDERVULKAN_RENDERENGINECORE_HPP
