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
			class Device;
			class Surface;
			class Swapchain;

			struct SwapchainBuilderData;

			class SwapchainBuilder
			{
			public:
				explicit SwapchainBuilder(std::shared_ptr<const Device> device,
					std::weak_ptr<const Surface> surface, std::shared_ptr<const config::IRenderConfig> config);
				~SwapchainBuilder();

				std::shared_ptr<Swapchain> build();
				std::shared_ptr<Swapchain> rebuild(std::shared_ptr<const Swapchain> oldSwapchain);
				void destroy(std::shared_ptr<const Swapchain> swapchain);
			protected:
			private:
				std::shared_ptr<SwapchainBuilderData> data_;
				std::shared_ptr<const Device> device_;
				std::weak_ptr<const Surface> surface_;
				std::shared_ptr<const config::IRenderConfig> config_;
			};
		}
	}
}

#endif // SWAPCHAINBUILDER_HPP
