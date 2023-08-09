#pragma once

#include <engine/render/ISubRenderPipeline.hpp>
#include <engine/world/RenderChunk.hpp>
#include <engine/pipeline/IRenderEngineWorldPipelineSubscriber.hpp>
#include <tools/SpinLock.hpp>
#include <util/ISubscription.hpp>

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
}

namespace CubA4::render::engine::pipeline
{
	class RenderEngineWorldPipeline;

	class ChunkSubRenderPipeline :
		public virtual ISubRenderPipeline,
		public virtual IRenderEngineWorldPipelineSubscriber
	{
		struct OldChunksInfo
		{
			uint32_t cyclesLeft;
			std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> oldChunks;
		};
	public:
		explicit ChunkSubRenderPipeline(std::shared_ptr<pipeline::RenderEngineWorldPipeline> worldPipeline, SubpipelineVersion incrementCount);
		~ChunkSubRenderPipeline();

		void onIterate() override;
		void executeFrom(VkCommandBuffer primaryCmdBuffer) override;

		uint32_t getSubpass() const override;
		SubpipelineVersion getVersion() const;

	private:
		void chunksUpdated(std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> renderChunks) override;
	private:
		uint32_t subpass_;
		std::vector<OldChunksInfo> oldChunks_;

		std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> chunks_;
		CubA4::render::tools::SpinLock chunkLock_;
		CubA4::render::tools::SpinLock oldChunksLock_;
		std::unique_ptr<CubA4::util::ISubscription> chunkUpdateSubscription_;

		SubpipelineVersion incrementCount_;
		std::atomic<SubpipelineVersion> version_;
	};
}
