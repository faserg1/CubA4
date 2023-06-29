#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <util/ISubscription.hpp>
#include <vulkan/FramebuffersBuilder.hpp>
#include <vulkan/Framebuffer.hpp>
#include <tools/SpinLock.hpp>
#include <engine/pipeline/IRenderEngineWorldPipelineSubscriber.hpp>
#include <engine/framebuffer/FramebufferManager.hpp>
#include <engine/RenderPassManager.hpp>

namespace CubA4::render
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
			class RenderEngineWorldPipeline;
		}

		class Render :
			public virtual pipeline::IRenderEngineWorldPipelineSubscriber
		{
			struct OldChunksInfo
			{
				uint32_t cyclesLeft;
				std::shared_ptr<const vulkan::Swapchain> oldSwapchain;
				std::vector<std::shared_ptr<vulkan::Framebuffer>> oldFramebuffers;
				std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> oldChunks;
			};
		public:
			explicit Render(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<RenderPassManager> rpManager,
			std::shared_ptr<FramebufferManager> framebufferManager,
				std::shared_ptr<const config::IRenderConfig> config);
			Render(const Render &) = delete;
			~Render();

			void setup(std::shared_ptr<pipeline::RenderEngineWorldPipeline> pipeline);
			void shutdown();

			void onAcquireFailed(std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);
			void onAcquire(uint32_t imgIndex);
			void record(std::shared_ptr<vulkan::Framebuffer> framebuffer);
			std::shared_ptr<const vulkan::Semaphore> send(std::shared_ptr<vulkan::Framebuffer> framebuffer, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);

			std::shared_ptr<const config::IRenderConfig> getConfig() const;
		protected:
		private:
			void onCycle();

			void chunksUpdated(std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> renderChunks) override;
		private:
			const std::shared_ptr<const vulkan::Device> device_;
			const std::shared_ptr<RenderPassManager> renderPassManager_;
			const std::shared_ptr<FramebufferManager> framebufferManager_;
			const std::shared_ptr<const config::IRenderConfig> config_;

			std::vector<OldChunksInfo> olChunks_;

			std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> chunks_;
			CubA4::render::tools::SpinLock chunkLock_;
			CubA4::render::tools::SpinLock oldChunksLock_;
			std::unique_ptr<CubA4::util::ISubscription> chunkUpdateSubscription_;
		};
	}
}
