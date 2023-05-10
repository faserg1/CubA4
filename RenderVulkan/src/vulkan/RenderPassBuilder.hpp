#pragma once

#include <memory>
#include <config/VulkanConfigAdapter.hpp>

namespace CubA4::render::vulkan
{
	class Device;
	class RenderPass;
	class Swapchain;

	class RenderPassBuilder
	{
	public:
		explicit RenderPassBuilder(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain, CubA4::render::config::VulkanConfigAdapter config);
		~RenderPassBuilder();

		std::shared_ptr<RenderPass> build();
	protected:
	private:
		const std::shared_ptr<const Device> device_;
		const std::shared_ptr<const Swapchain> swapchain_;
		const CubA4::render::config::VulkanConfigAdapter config_;
	};
}
