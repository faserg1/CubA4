#pragma once

#include <vulkan/Device.hpp>
#include <vulkan/RenderPassBuilder.hpp>
#include <vulkan/RenderPass.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <memory>

namespace CubA4::render::engine
{
	struct MainRenderPassInfo
	{
		uint32_t worldSubpass;
		uint32_t subpassCount = 0;
	};

	struct DebugRenderPassInfo
	{
		uint32_t debugSubpass;
	};

    class RenderPassManager
    {
    public:
		RenderPassManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config);
		void createRenderPasses(VkFormat imageFormat);

		std::shared_ptr<vulkan::RenderPass> getMainRenderPass() const;
		std::shared_ptr<vulkan::RenderPass> getDebugRenderPass() const;
		
		const MainRenderPassInfo& getMainInfo() const;
		const DebugRenderPassInfo& getDebugInfo() const;
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const CubA4::render::config::VulkanConfigAdapter config_;
		std::shared_ptr<vulkan::RenderPass> mainRenderPass_;
		std::shared_ptr<vulkan::RenderPass> debugRenderPass_;

		MainRenderPassInfo mainInfo_;
		DebugRenderPassInfo debugInfo_;
    };
}