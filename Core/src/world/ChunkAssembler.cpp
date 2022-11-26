#include <world/ChunkAssembler.hpp>
using namespace CubA4::world;

ChunkAssembler::ChunkAssembler()
{
	
}

ChunkAssembler::~ChunkAssembler()
{
	
}

ReassmebledChunkContainers ChunkAssembler::reassmeble(std::shared_ptr<Chunk> chunk, const ChunkBModification &modification)
{
    return {};
}

std::shared_ptr<ChunkBRange> ChunkAssembler::buildRange(
    std::shared_ptr<const CubA4::object::IBlock> block,
    const CubA4::world::BlockInChunkPos &start,
    const CubA4::world::BlockInChunkPos &end,
    BlockData data,
    CubA4::world::Layer layer)
{
    return std::make_shared<ChunkBRange>(block, std::array{start, end}, data, layer);
}