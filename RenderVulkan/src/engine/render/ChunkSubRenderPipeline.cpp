#include <engine/render/ChunkSubRenderPipeline.hpp>
#include <engine/pipeline/RenderEngineWorldPipeline.hpp>
using namespace CubA4::render::engine::pipeline;

ChunkSubRenderPipeline::ChunkSubRenderPipeline(std::shared_ptr<pipeline::RenderEngineWorldPipeline> worldPipeline, SubpipelineVersion incrementCount) :
	subpass_(worldPipeline->getSubpassNumber()), incrementCount_(incrementCount), version_(0)
{
	chunkUpdateSubscription_ = worldPipeline->subscribe(this);
}

ChunkSubRenderPipeline::~ChunkSubRenderPipeline() = default;

void ChunkSubRenderPipeline::onIterate()
{
	auto locker = oldChunksLock_.lock();
	auto it = std::remove_if(oldChunks_.begin(), oldChunks_.end(), [](OldChunksInfo &oldInfo) -> bool
	{
		if (oldInfo.cyclesLeft > 0)
			oldInfo.cyclesLeft--;
		return !oldInfo.cyclesLeft;
	});
	oldChunks_.erase(it, oldChunks_.end());
}

void ChunkSubRenderPipeline::executeFrom(VkCommandBuffer primaryCmdBuffer)
{
	decltype(chunks_) chunks;

	{
		auto locker = chunkLock_.lock();
		chunks = chunks_;
	}

	for (auto chunk : chunks)
	{
		if (!chunk)
			continue;
		chunk->executeFrom(primaryCmdBuffer);
	}
}

uint32_t ChunkSubRenderPipeline::getSubpass() const
{
	return subpass_;
}

ChunkSubRenderPipeline::SubpipelineVersion ChunkSubRenderPipeline::getVersion() const
{
	return version_;
}

void ChunkSubRenderPipeline::chunksUpdated(std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> renderChunks)
{
	{
		auto locker = chunkLock_.lock();
		auto locker2 = oldChunksLock_.lock();
		oldChunks_.push_back(OldChunksInfo {
			.cyclesLeft = 10,
			.oldChunks = chunks_
		});
		chunks_ = renderChunks;
	}
	version_.fetch_add(incrementCount_);
}