#pragma once

#include <vulkan/Device.hpp>
#include <vulkan/FramebuffersBuilder.hpp>
#include <vulkan/FramebufferImage.hpp>
#include <vulkan/RenderPass.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <tools/SpinLock.hpp>
#include <memory>

namespace CubA4::render::engine
{
    class FramebufferManager
    {
		struct OldFramebufferInfo
		{
			uint32_t cyclesLeft;
			std::shared_ptr<const vulkan::Swapchain> oldSwapchain;
			std::vector<std::shared_ptr<vulkan::Framebuffer>> oldFramebuffers;
		};
    public:
        FramebufferManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config);

		void setRenderPass(std::shared_ptr<const vulkan::RenderPass> renderPass);

		void onSwapchainUpdate(std::shared_ptr<const vulkan::Swapchain> swapchain);
		std::shared_ptr<vulkan::Framebuffer> onAcquire(uint32_t imgIndex);
		std::shared_ptr<vulkan::Framebuffer> get(uint32_t imgIndex) const;
		void onAcquireFailed();
		void markDirty();

		VkExtent2D getExtent() const;
		uint32_t getImageCount() const;
		uint32_t getAttachmentsCount() const;
	protected:
		virtual void onSwapchainUpdateInternal(
			std::shared_ptr<const vulkan::Swapchain> swapchain) = 0;
	protected:
		const std::shared_ptr<const vulkan::Device> device_;
        const CubA4::render::config::VulkanConfigAdapter config_;
		vulkan::CommandPool commandPool_;
		std::weak_ptr<const vulkan::RenderPass> renderPass_;

		std::shared_ptr<const vulkan::Swapchain> currentSwapchain_;
		std::vector<std::shared_ptr<vulkan::Framebuffer>> framebuffers_;

		uint32_t attachmentsCount_ = 0;
	private:
		void onCycle();
    private:
		std::vector<OldFramebufferInfo> oldFramebuffers_;

		CubA4::render::tools::SpinLock oldFramebuffersLock_;
    };
}