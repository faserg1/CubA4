#include "./RenderChunk.hpp"
using namespace CubA4::render::engine::world;
using namespace CubA4::core::world;
using namespace CubA4::mod::world;

RenderChunk::RenderChunk(const ChunkPos &pos, std::vector<VkCommandBuffer> cmdBuffers, std::function<void()> deleter) :
	pos_(pos), cmdBuffers_(std::move(cmdBuffers)), deleter_(deleter)
{
	
}

RenderChunk::~RenderChunk()
{
	deleter_();
}

const ChunkPos &RenderChunk::getChunkPos() const
{
	return pos_;
}

void RenderChunk::executeFrom(VkCommandBuffer primaryCmdBuffer) const
{
	vkCmdExecuteCommands(primaryCmdBuffer, static_cast<uint32_t>(cmdBuffers_.size()), cmdBuffers_.data());
}