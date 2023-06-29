#pragma once

#include <engine/framebuffer/FramebufferManager.hpp>

namespace CubA4::render::engine
{
    class DebugFramebufferManager : public FramebufferManager
	{
	public:
		DebugFramebufferManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config);
		void setMainDepths(std::vector<VkImage> mainDepths);
	protected:
		void onSwapchainUpdateInternal(std::shared_ptr<const vulkan::Swapchain> swapchain) override;
	private:
		std::vector<VkImage> mainDepths_;
	};
}