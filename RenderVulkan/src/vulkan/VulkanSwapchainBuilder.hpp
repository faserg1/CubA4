#ifndef SWAPCHAINBUILDER_HPP
#define SWAPCHAINBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace config
		{
			class IRenderConfig;
		}

		namespace vulkan
		{
			class VulkanDevice;
			class VulkanSurface;
			class VulkanSwapchain;

			struct VulkanSwapchainBuilderData;

			class VulkanSwapchainBuilder
			{
			public:
				explicit VulkanSwapchainBuilder(std::shared_ptr<const VulkanDevice> device,
					std::weak_ptr<const VulkanSurface> surface, std::shared_ptr<const config::IRenderConfig> config);
				~VulkanSwapchainBuilder();

				std::shared_ptr<VulkanSwapchain> build();
				std::shared_ptr<VulkanSwapchain> rebuild(std::shared_ptr<const VulkanSwapchain> oldSwapchain);
				void destroy(std::shared_ptr<const VulkanSwapchain> swapchain);
			protected:
			private:
				std::shared_ptr<VulkanSwapchainBuilderData> data_;
				std::shared_ptr<const VulkanDevice> device_;
				std::weak_ptr<const VulkanSurface> surface_;
				std::shared_ptr<const config::IRenderConfig> config_;
			};
		}
	}
}

#endif // SWAPCHAINBUILDER_HPP
