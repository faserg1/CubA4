#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <util/ISubscription.hpp>
#include <vulkan/FramebuffersBuilder.hpp>
#include <vulkan/Framebuffer.hpp>
#include <tools/SpinLock.hpp>
#include "./pipeline/IRenderEnginePipelineSubscriber.hpp"

namespace CubA4
{
	namespace render
	{
		namespace config
		{
			class IRenderConfig;
		}

		namespace vulkan
		{
			class Device;
			class Memory;
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
				struct OldFramebufferInfo
				{
					uint32_t cyclesLeft;
					std::shared_ptr<const vulkan::Swapchain> oldSwapchain;
					std::vector<std::shared_ptr<vulkan::Framebuffer>> oldFramebuffers;
					std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> oldChunks;
				};
			public:
				explicit Render(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::Swapchain> swapchain, std::shared_ptr<const config::IRenderConfig> config);
				explicit Render(const Render &) = delete;
				~Render();

				void setup(std::shared_ptr<pipeline::RenderEnginePipeline> pipeline);
				void shutdown();

				void swapchainChanged(std::shared_ptr<const vulkan::Swapchain> swapchain);
				void onAcquireFailed(std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);
				std::shared_ptr<vulkan::Framebuffer> onAcquire(uint32_t imgIndex);
				void record(std::shared_ptr<vulkan::Framebuffer> framebuffer);
				std::shared_ptr<const vulkan::Semaphore> send(std::shared_ptr<vulkan::Framebuffer> framebuffer, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);

				std::shared_ptr<const vulkan::RenderPass> getRenderPass() const;

				std::shared_ptr<const config::IRenderConfig> getConfig() const;
			protected:
				void createFramebuffers();
				void destroyFramebuffers();

				void createRenderPass();
				void destroyRenderPass();
			private:
				void onCycle();

				void chunksUpdated(std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> renderChunks) override;
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<const config::IRenderConfig> config_;
				std::shared_ptr<const vulkan::Swapchain> swapchain_;
				vulkan::FramebuffersBuilder framebuffersBuilder_;

				std::shared_ptr<const vulkan::RenderPass> renderPass_;
				std::vector<std::shared_ptr<vulkan::Framebuffer>> framebuffers_;
	
				std::vector<OldFramebufferInfo> oldFramebuffers_;

				std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> chunks_;
				CubA4::render::tools::SpinLock chunkLock_;
				CubA4::render::tools::SpinLock oldFramebuffersLock_;
				std::unique_ptr<CubA4::util::ISubscription> chunkUpdateSubscription_;
			};
		}
	}
}
