#pragma once

#include <engine/framebuffer/FramebufferManager.hpp>

namespace CubA4::render::engine
{
    class MainFramebufferManager : public FramebufferManager
	{
	public:
		MainFramebufferManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config);
	protected:
		void onSwapchainUpdateInternal(std::shared_ptr<const vulkan::Swapchain> swapchain) override;
	};
}