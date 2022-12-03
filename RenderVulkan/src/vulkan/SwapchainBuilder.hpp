#pragma once

#include <memory>
#include <config/IRenderConfig.hpp>
#include <vulkan/vulkan.h>

namespace CubA4::render::vulkan
{
	class Device;
	class Surface;
	class Swapchain;

	struct SwapchainBuilderData;

	class SwapchainBuilder
	{
	public:
		explicit SwapchainBuilder(std::shared_ptr<const Device> device,
			std::weak_ptr<const Surface> surface, std::shared_ptr<config::IRenderConfig> config);
		~SwapchainBuilder();

		std::shared_ptr<Swapchain> build(std::shared_ptr<const Swapchain> oldSwapchain = {});
		void destroy(std::shared_ptr<const Swapchain> swapchain);
	protected:
		VkFormat getFormat();
		VkPresentModeKHR getPresentMode();
	private:
		std::shared_ptr<const Device> device_;
		std::weak_ptr<const Surface> surface_;
		std::shared_ptr<config::IRenderConfig> config_;
	};
}
