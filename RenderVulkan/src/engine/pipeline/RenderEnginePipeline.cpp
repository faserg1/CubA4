#include "./RenderEnginePipeline.hpp"
#include "./RenderChunkCompiler.hpp"
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/map.hpp>
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;

RenderEnginePipeline::RenderEnginePipeline(std::shared_ptr<RenderChunkCompiler> chunkCompiler, RenderChunkPipelineData data) :
	chunkCompiler_(chunkCompiler), data_(data)
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
		compileChunk.emplace([this, chunk, data = data_]{
			auto compiledChunk = chunkCompiler_->compileChunk(chunk, data);
			updateChunk(compiledChunk);
		});
		exec_.run(std::move(compileChunk));
	}
}

void RenderEnginePipeline::onFramebufferUpdated(const RenderChunkPipelineData &data)
{
	data_ = data;
	for (auto &[pos, chunk] : chunks_)
	{
		auto compiledChunk = chunkCompiler_->compileChunk(chunk, data);
		chunk.swap(compiledChunk);
	}

	auto chunks = chunks_ | ranges::views::values | ranges::to<std::vector>;
	
	subHelper_.apply([chunks](auto *sub)
	{
		sub->chunksUpdated(chunks);
	});
}

std::unique_ptr<CubA4::util::ISubscription> RenderEnginePipeline::subscribe(IRenderEnginePipelineSubscriber *subscriber)
{
	return std::move(subHelper_.add(subscriber));
}

void RenderEnginePipeline::updateChunk(sRenderChunk chunk)
{
	auto data = chunk->getPipelineData();
	if (data != data_)
	{
		data = data_;
		chunk = chunkCompiler_->compileChunk(chunk, data);
	}
	chunks_.insert_or_assign(chunk->getChunkPos(), chunk);
	auto chunks = chunks_ | ranges::views::values | ranges::to<std::vector>;
	
	subHelper_.apply([chunks](auto *sub)
	{
		sub->chunksUpdated(chunks);
	});
}

void RenderEnginePipeline::dropChunk(const CubA4::world::ChunkPos &chunkPos)
{
	auto toRemove = chunks_.find(chunkPos);
	if (toRemove != chunks_.end())
		chunks_.erase(toRemove);
}