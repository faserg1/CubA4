#pragma once

#include <vulkan/Device.hpp>
#include <vulkan/Swapchain.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/RenderPass.hpp>
#include <engine/memory/MemoryAllocator.hpp>
#include <vulkan/Framebuffer.hpp>
#include <memory>
#include <vector>

namespace CubA4::render::vulkan
{
	class FramebuffersBuilder
	{
	public:
		explicit FramebuffersBuilder(std::shared_ptr<const vulkan::Device> device);
		~FramebuffersBuilder();

		[[nodiscard]] std::vector<std::shared_ptr<Framebuffer>> createFramebuffers(std::shared_ptr<const Swapchain> swapchain, std::shared_ptr<const vulkan::RenderPass> renderPass);

		// TODO: [OOKAMI] Make framebuffer not from swapchain, but with same parameters
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		CubA4::render::engine::memory::MemoryAllocator allocator_;
		CommandPool commandPool_;
	};
}
