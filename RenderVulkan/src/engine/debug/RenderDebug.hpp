#pragma once

#include <memory>
#include <vector>
#include <engine/debug/IRenderDebug.hpp>
#include <engine/debug/IRenderDebugInternal.hpp>
#include <engine/debug/RenderDebugCollection.hpp>
#include <engine/pipeline/IMainEnginePipelineItem.hpp>
#include <engine/RenderPassManager.hpp>
#include <engine/world/WorldManager.hpp>
#include <engine/material/ShaderFactory.hpp>
#include <engine/framebuffer/DebugFramebufferManager.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/pipeline/Pipeline.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <engine/memory/MemoryManager.hpp>
#include <engine/memory/MemoryHelper.hpp>
#include <mutex>

namespace CubA4::render::engine
{
	class ResourceManager;
}

namespace CubA4::render::engine::debug
{
	class RenderDebug :
		public std::enable_shared_from_this<RenderDebug>,
		public virtual IRenderDebugInternal,
		public virtual IRenderDebug, public virtual CubA4::render::engine::pipeline::IMainEnginePipelineItem
	{
	public:
		RenderDebug(std::shared_ptr<const vulkan::Device> device,
			std::shared_ptr<const RenderPassManager> rpManager,
			std::shared_ptr<CubA4::render::engine::ResourceManager> resManager,
			std::shared_ptr<const CubA4::render::engine::world::WorldManager> worldManager,
			CubA4::render::config::VulkanConfigAdapter config);
		[[nodiscard]] std::shared_ptr<IRenderDebugCollection> addCollection() override;
		void setEnabled(bool enabled = true) override;
		bool isEnabled() const override;

		void swapchainChanged(std::shared_ptr<const CubA4::render::vulkan::Swapchain> swapchain, std::vector<VkImage> mainDepths);

		void onRenderPassCreated();
		void setup();
		
		std::shared_ptr<const vulkan::Semaphore> render(uint32_t frame,
			std::shared_ptr<const vulkan::Semaphore> awaitSemaphore) override;
	private:
		void onCommandsDirty() override;
		std::shared_ptr<CubA4::render::vulkan::Pipeline> getPipeline(PipelineType type) const override;
		DebugRenderModel createBuffer(std::vector<VertexColor> vertices) override;
		CubA4::render::vulkan::sVkDescriptorSet getWorldDescriptorSet() override;

		void record(uint32_t frame);
		void send(uint32_t frame, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);
		void createPipelines();
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const std::shared_ptr<const RenderPassManager> rpManager_;
		const std::shared_ptr<CubA4::render::engine::ResourceManager> resManager_;
		std::shared_ptr<const CubA4::render::engine::world::WorldManager> worldManager_;
		const CubA4::render::config::VulkanConfigAdapter config_;
		const std::unique_ptr<DebugFramebufferManager> framebufferManager_;
		const std::shared_ptr<CubA4::render::engine::memory::MemoryManager> memoryManager_;
		const std::shared_ptr<CubA4::render::engine::memory::MemoryHelper> memoryHelper_;
		engine::material::ShaderFactory shaderFactory_;
		vulkan::CommandPool cmdPool_;
		std::vector<std::weak_ptr<RenderDebugCollection>> collections_;
		bool enabled_ = false;

		std::shared_ptr<vulkan::Pipeline> line_;
		std::shared_ptr<vulkan::Pipeline> wireframe_;

		std::mutex deviceLock_;
	};
}