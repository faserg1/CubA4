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
	class FramebuffersBuilder
	{
	public:
		explicit FramebuffersBuilder(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config);
		~FramebuffersBuilder();

		[[nodiscard]] std::vector<std::shared_ptr<Framebuffer>> createFramebuffers(std::shared_ptr<const Swapchain> swapchain, std::shared_ptr<const vulkan::RenderPass> renderPass);
		[[nodiscard]] std::shared_ptr<FramebufferImage> createImageWithMemory(VkFormat format, VkExtent2D resolution, VkImageUsageFlags usage, VkImageAspectFlags aspectFlags, VkImageLayout initLayout = VK_IMAGE_LAYOUT_UNDEFINED);
	private:
		
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const CubA4::render::config::VulkanConfigAdapter config_;
		CubA4::render::engine::memory::MemoryAllocator allocator_;
		CommandPool commandPool_;
	};
}
