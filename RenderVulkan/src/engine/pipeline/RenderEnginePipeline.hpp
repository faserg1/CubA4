#pragma once

#include <memory>
#include <vector>
#include <map>
#include <thread>
#include <atomic>
#include <util/SubscriptionHelper.hpp>
#include <taskflow/taskflow.hpp>

#include "IRenderEnginePipelineSubscriber.hpp"
#include "IRenderEnginePipelineUpdater.hpp"

namespace CubA4::render::engine
{
	namespace world
	{
		class RenderChunk;
	}

	namespace pipeline
	{
		class RenderChunkCompiler;

		class RenderEnginePipeline :
			public virtual IRenderEnginePipelineUpdater
		{
		public:
			using sRenderChunk = std::shared_ptr<const world::RenderChunk>;
			explicit RenderEnginePipeline(std::shared_ptr<RenderChunkCompiler> chunkCompiler, RenderChunkPipelineData data);
			~RenderEnginePipeline();

			void pushChunks(std::vector<std::shared_ptr<const CubA4::world::IChunk>> chunks) override;
			void onFramebufferUpdated(const RenderChunkPipelineData &data) override;

			std::unique_ptr<CubA4::util::ISubscription> subscribe(IRenderEnginePipelineSubscriber *subscriber);
		protected:
		private:
			void updateChunk(sRenderChunk chunk);
			void dropChunk(const CubA4::world::ChunkPos &chunkPos);
		private:
			const std::shared_ptr<RenderChunkCompiler> chunkCompiler_;
			tf::Executor exec_;
			CubA4::util::SubscriptionHelper<IRenderEnginePipelineSubscriber> subHelper_;
			RenderChunkPipelineData data_;
			std::map<CubA4::world::ChunkPos, sRenderChunk> chunks_;
		};
	}
}
