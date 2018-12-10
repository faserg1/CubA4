#ifndef RENDERVULKAN_RENDERENGINEPIPELINE_HPP
#define RENDERVULKAN_RENDERENGINEPIPELINE_HPP

#include <memory>
#include <vector>
#include <queue>
#include <future>
#include <thread>
#include <atomic>
#include <util/SubscriptionHelper.hpp>

#include "IRenderEnginePipelineSubscriber.hpp"
#include "IRenderEnginePipelineUpdater.hpp"

namespace CubA4
{
	namespace render
	{
		namespace engine
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
					explicit RenderEnginePipeline(std::shared_ptr<RenderChunkCompiler> chunkCompiler);
					~RenderEnginePipeline();

					void pushChunks(std::vector<std::shared_ptr<const CubA4::mod::world::IChunk>> chunks) override;

					std::unique_ptr<CubA4::core::util::ISubscription> subscribe(IRenderEnginePipelineSubscriber *subscriber);
				protected:
				private:
					void handlerLoop();
				private:
					const std::shared_ptr<RenderChunkCompiler> chunkCompiler_;
					std::queue<std::future<sRenderChunk>> chunkQueue_;
					CubA4::core::util::SubscriptionHelper<IRenderEnginePipelineSubscriber> subHelper_;
					std::thread handlerThread_;
					std::atomic_bool run_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_RENDERENGINEPIPELINE_HPP
