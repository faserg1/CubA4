#include "./RenderEnginePipeline.hpp"
#include "./RenderChunkCompiler.hpp"
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;

RenderEnginePipeline::RenderEnginePipeline(std::shared_ptr<RenderChunkCompiler> chunkCompiler) :
	chunkCompiler_(chunkCompiler)
{
	
}

RenderEnginePipeline::~RenderEnginePipeline()
{
	
}

void RenderEnginePipeline::pushChunks(std::vector<std::shared_ptr<const CubA4::world::IChunk>> chunks)
{
	for (auto chunk : chunks)
	{
		tf::Taskflow compileChunk;
		compileChunk.emplace([this, chunk]{
			auto compiledChunk = chunkCompiler_->compileChunk(chunk).get();
			subHelper_.apply([compiledChunk](auto *sub)
			{
				sub->chunkCompiled(compiledChunk);
			});
		});
		exec_.run(std::move(compileChunk));
	}
}

std::unique_ptr<CubA4::util::ISubscription> RenderEnginePipeline::subscribe(IRenderEnginePipelineSubscriber *subscriber)
{
	return std::move(subHelper_.add(subscriber));
}
