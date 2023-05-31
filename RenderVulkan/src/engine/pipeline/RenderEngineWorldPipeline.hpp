#pragma once

#include <memory>
#include <vector>
#include <map>
#include <thread>
#include <atomic>
#include <util/SubscriptionHelper.hpp>
#include <taskflow/taskflow.hpp>
#include <engine/pipeline/IRenderEngineWorldPipeline.hpp>
#include <engine/pipeline/IRenderEngineWorldPipelineSubscriber.hpp>

namespace CubA4::render::engine
{
	namespace world
	{
		class RenderChunk;
	}

	namespace pipeline
	{
		class RenderChunkCompiler;


		// World pipeline?
		class RenderEngineWorldPipeline :
			public virtual IRenderEngineWorldPipeline
		{
		public:
			using sRenderChunk = std::shared_ptr<const world::RenderChunk>;
			explicit RenderEngineWorldPipeline(std::shared_ptr<RenderChunkCompiler> chunkCompiler, RenderFramebufferData data);
			~RenderEngineWorldPipeline();

			void pushChunks(std::vector<std::shared_ptr<const CubA4::world::IChunk>> chunks) override;
			void onFramebufferUpdated(const RenderFramebufferData &data) override;

			std::unique_ptr<CubA4::util::ISubscription> subscribe(IRenderEngineWorldPipelineSubscriber *subscriber);
		protected:
		private:
			void updateChunk(sRenderChunk chunk);
			void dropChunk(const CubA4::world::ChunkPos &chunkPos);
		private:
			const std::shared_ptr<RenderChunkCompiler> chunkCompiler_;
			tf::Executor exec_;
			CubA4::util::SubscriptionHelper<IRenderEngineWorldPipelineSubscriber> subHelper_;
			RenderFramebufferData data_;
			std::map<CubA4::world::ChunkPos, sRenderChunk> chunks_;
		};
	}
}
