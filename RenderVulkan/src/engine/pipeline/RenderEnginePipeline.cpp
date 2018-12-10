#include "./RenderEnginePipeline.hpp"
#include "./RenderChunkCompiler.hpp"
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;

RenderEnginePipeline::RenderEnginePipeline(std::shared_ptr<RenderChunkCompiler> chunkCompiler) :
	chunkCompiler_(chunkCompiler), run_(true)
{
	handlerThread_ = std::thread(&RenderEnginePipeline::handlerLoop, this);
}

RenderEnginePipeline::~RenderEnginePipeline()
{
	run_ = false;
	handlerThread_.join();
}

void RenderEnginePipeline::pushChunks(std::vector<std::shared_ptr<const CubA4::mod::world::IChunk>> chunks)
{
	for (auto chunk : chunks)
	{
		auto futureRenderChunk = chunkCompiler_->compileChunk(chunk);
		chunkQueue_.push(std::move(futureRenderChunk));
	}
}

std::unique_ptr<CubA4::core::util::ISubscription> RenderEnginePipeline::subscribe(IRenderEnginePipelineSubscriber *subscriber)
{
	return std::move(subHelper_.add(subscriber));
}

void RenderEnginePipeline::handlerLoop()
{
	// RAII
	struct YieldOnDestroy
	{
		~YieldOnDestroy()
		{
			std::this_thread::yield();
		}
	};

	while (run_)
	{
		YieldOnDestroy y;
		if (!chunkQueue_.size())
			continue;
		auto fRenderChunk = std::move(chunkQueue_.front());
		chunkQueue_.pop();
		auto sRenderChunk = fRenderChunk.get();
		subHelper_.apply([sRenderChunk](auto *sub)
		{
			sub->chunkCompiled(sRenderChunk);
		});
	}
}