#pragma once

#include <vulkan/Device.hpp>
#include <vulkan/Swapchain.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/RenderPass.hpp>
#include <engine/memory/MemoryAllocator.hpp>
#include <engine/memory/MemoryManager.hpp>
#include <vulkan/Framebuffer.hpp>
#include <vulkan/FramebufferImage.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <memory>
#include <vector>

namespace CubA4::render::vulkan
{
	struct AttachmentInfo
	{
		enum class Type {
			Input,
			Color,
			Depth,
			Resolve,
			Present,
		} type;
		// if created from another source, do not use for swapchain (Present)
		std::vector<VkImage> external;
		/// Ignored if type == Present
		VkImageUsageFlags additionalUsage;
		VkImageAspectFlags aspect;
		/// Ignored if type == Present
		bool enableAA = false;
	};

	class FramebuffersBuilder
	{
	public:
		explicit FramebuffersBuilder(std::shared_ptr<const vulkan::Device> device, CommandPool &commandPool, CubA4::render::config::VulkanConfigAdapter config);
		~FramebuffersBuilder();

		uint32_t addAttachmentInfo(const AttachmentInfo &info);
		uint32_t getAttachmentsCount() const;

		[[nodiscard]] std::vector<std::shared_ptr<Framebuffer>> createFramebuffers(std::shared_ptr<const Swapchain> swapchain, std::shared_ptr<const vulkan::RenderPass> renderPass);
		[[nodiscard]] std::shared_ptr<FramebufferImage> createImageWithMemory(VkFormat format, VkExtent2D resolution, VkImageUsageFlags usage, VkImageAspectFlags aspectFlags, bool aa, VkImageLayout initLayout = VK_IMAGE_LAYOUT_UNDEFINED);
	private:
		
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const CubA4::render::config::VulkanConfigAdapter config_;
		CommandPool &commandPool_;
		CubA4::render::engine::memory::MemoryAllocator allocator_;

		std::vector<AttachmentInfo> attachmentInfos_;
	};
}
