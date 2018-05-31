#ifndef VULKANRENDERENGINE_HPP
#define VULKANRENDERENGINE_HPP

#include <engine/IRenderEngine.hpp>
#include <vector>

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
			class VulkanInstance;
			class VulkanInstanceBuilder;
			class VulkanDevice;
			class VulkanDeviceBuilder;
			class VulkanSurface;
			class VulkanSwapchain;
			class VulkanSwapchainBuilder;

			namespace addon
			{
				class VulkanInstanceAddon;
				class VulkanDeviceAddon;
			}
		}

		namespace engine
		{
			class VulkanRenderEngine :
				public virtual IRenderEngine
			{
			public:
				explicit VulkanRenderEngine(std::shared_ptr<const core::info::IApplicationInfo> info, std::shared_ptr<const core::ICore> core);
				explicit VulkanRenderEngine(const VulkanRenderEngine &) = delete;
				~VulkanRenderEngine();

				void init(std::shared_ptr<window::IWindow> window) override;
				void destroy() override;
			protected:
				void initInstance();
				void destroyInstance();

				void initDevice();
				void destroyDevice();

				void initSwapchain();
				void rebuildSwapchain();
				void destroySwapchain();
			private:
				std::shared_ptr<const core::info::IApplicationInfo> info_;
				std::shared_ptr<const core::ICore> core_;
				std::shared_ptr<core::logging::ILogger> logger_;
				std::shared_ptr<config::IRenderConfig> config_;

				std::weak_ptr<window::IWindow> window_;
				std::weak_ptr<const vulkan::VulkanSurface> surface_;

				std::shared_ptr<vulkan::VulkanInstanceBuilder> instanceBuilder_;
				std::shared_ptr<const vulkan::VulkanInstance> instance_;
				std::vector<std::shared_ptr<vulkan::addon::VulkanInstanceAddon>> instanceAddons_;

				std::shared_ptr<vulkan::VulkanDeviceBuilder> deviceBuilder_;
				std::shared_ptr<const vulkan::VulkanDevice> device_;
				std::vector<std::shared_ptr<vulkan::addon::VulkanDeviceAddon>> deviceAddons_;

				std::shared_ptr<vulkan::VulkanSwapchainBuilder> swapchainBuilder_;
				std::shared_ptr<const vulkan::VulkanSwapchain> swapchain_;
			};
		}
	}
}

#endif // VULKANRENDERENGINE_HPP
