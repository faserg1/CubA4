#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <util/ISubscription.hpp>
#include <vulkan/FramebuffersBuilder.hpp>
#include <vulkan/Framebuffer.hpp>
#include <vulkan/QueryPool.hpp>
#include <tools/SpinLock.hpp>
#include <engine/render/ISubRenderPipeline.hpp>
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
			class RenderEntityPipeline;
		}

		class Render
		{
			struct OldFramebuffersInfo
			{
				uint32_t cyclesLeft;
				std::shared_ptr<const vulkan::Swapchain> oldSwapchain;
				std::vector<std::shared_ptr<vulkan::Framebuffer>> oldFramebuffers;
			};

			using ISubpipeline = CubA4::render::engine::pipeline::ISubRenderPipeline;
			using SubpipelineVersion = ISubpipeline::SubpipelineVersion;
		public:
			explicit Render(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<RenderPassManager> rpManager,
			std::shared_ptr<FramebufferManager> framebufferManager,
				std::shared_ptr<const config::IRenderConfig> config);
			Render(const Render &) = delete;
			~Render();

			void addSubPipeline(std::unique_ptr<ISubpipeline> &&subPipeline);
			void shutdown();

			void onAcquireFailed(std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);
			void onAcquire(uint32_t imgIndex);
			void record(std::shared_ptr<vulkan::Framebuffer> framebuffer, uint32_t imgIndex);
			std::shared_ptr<const vulkan::Semaphore> send(std::shared_ptr<vulkan::Framebuffer> framebuffer, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);

			std::shared_ptr<const config::IRenderConfig> getConfig() const;
		protected:
			void onIterate();
		private:
			const std::shared_ptr<const vulkan::Device> device_;
			const std::shared_ptr<RenderPassManager> renderPassManager_;
			const std::shared_ptr<FramebufferManager> framebufferManager_;
			const std::shared_ptr<const config::IRenderConfig> config_;

			std::shared_ptr<vulkan::QueryPool> queryPool_;
			uint32_t queryIndex_ = 0; //TODO: ???????????????????????

			std::vector<std::pair<std::unique_ptr<ISubpipeline>, SubpipelineVersion>> subPipelines_;

			std::vector<OldFramebuffersInfo> oldFramebuffers_;
			CubA4::render::tools::SpinLock oldFramebuffersLock_;
		};
	}
}
