#ifndef RENDERVULKAN_RENDER_HPP
#define RENDERVULKAN_RENDER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <util/ISubscription.hpp>
#include "./pipeline/IRenderEnginePipelineSubscriber.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			class Swapchain;
			class Semaphore;
			class RenderPass;
		}

		namespace engine
		{
			namespace pipeline
			{
				class RenderEnginePipeline;
			}

			class Render :
				public virtual pipeline::IRenderEnginePipelineSubscriber
			{
			public:
				explicit Render(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::Swapchain> swapchain);
				explicit Render(const Render &) = delete;
				~Render();

				void setup(std::shared_ptr<pipeline::RenderEnginePipeline> pipeline);
				void shutdown();

				void record(uint32_t imgIndex);
				std::shared_ptr<const vulkan::Semaphore> send(uint32_t imgIndex, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);

				std::shared_ptr<const vulkan::RenderPass> getRenderPass() const;
			protected:
				void createMainCommandPool();
				void destroyMainCommandPool();

				void createFramebuffers();
				void destroyFramebuffers();

				void createRenderPass();
				void destroyRenderPass();
			private:
				void chunkCompiled(std::shared_ptr<const CubA4::render::engine::world::RenderChunk> renderChunk) override;
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<const vulkan::Swapchain> swapchain_;
				VkCommandPool mainCommandPool_;

				struct FramebufferData
				{
					FramebufferData() = default;
					FramebufferData(const FramebufferData &) {}
					VkFence fence;
					VkFramebuffer framebuffer;
					VkImage image;
					VkImageView imageView;
					VkCommandBuffer cmdBuffer;
					std::shared_ptr<const vulkan::Semaphore> renderDoneSemaphore;
					std::atomic_bool dirty = true;
				};
				std::vector<FramebufferData> framebuffersData_;

				std::shared_ptr<const vulkan::RenderPass> renderPass_;
				std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> chunks_;
				std::atomic_bool chunksLocked_;
				std::unique_ptr<CubA4::core::util::ISubscription> chunkUpdateSubscription_;
			};
		}
	}
}

#endif // RENDERVULKAN_RENDER_HPP
