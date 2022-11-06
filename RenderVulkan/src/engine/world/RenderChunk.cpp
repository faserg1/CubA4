#include "./RenderChunk.hpp"
using namespace CubA4::render::engine::world;
using namespace CubA4::world;
using namespace CubA4::world;

RenderChunk::RenderChunk(Data data, std::function<void()> deleter) :
	data_(data), deleter_(deleter)
{
	
}

RenderChunk::~RenderChunk()
{
	deleter_();
}

const ChunkPos &RenderChunk::getChunkPos() const
{
	return data_.pos;
}

void RenderChunk::executeFrom(VkCommandBuffer primaryCmdBuffer) const
{
	vkCmdExecuteCommands(primaryCmdBuffer, static_cast<uint32_t>(data_.cmdBuffers.size()), data_.cmdBuffers.data());
}