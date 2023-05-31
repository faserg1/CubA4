#pragma once

#include <vulkan/Device.hpp>
#include <vulkan/RenderPassBuilder.hpp>
#include <vulkan/RenderPass.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <memory>

namespace CubA4::render::engine
{
    class RenderPassManager
    {
    public:
		RenderPassManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config);
		void createRenderPasses(VkFormat imageFormat);

		std::shared_ptr<vulkan::RenderPass> getMainRenderPass() const;
		static constexpr uint32_t getWorldSubpass() { return 0; }
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const CubA4::render::config::VulkanConfigAdapter config_;
		std::shared_ptr<vulkan::RenderPass> mainRenderPass_;
    };
}