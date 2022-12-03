#include <world/ChunkBSet.hpp>
using namespace CubA4::world;

ChunkBSet::ChunkBSet(std::vector<BlockInChunkPos> positions, BlockData data, Layer layer) :
    positions_(std::move(positions)), data_(std::move(data)), layer_(layer)
{
	
}

ChunkBSet::~ChunkBSet()
{
	
}

std::shared_ptr<const CubA4::object::IBlock> ChunkBSet::getBlock() const
{
    return {};
}

uint32_t ChunkBSet::getBlockCount() const
{
    return {};
}

bool ChunkBSet::hasBlockAt(const BlockInChunkPos &pos) const
{
    return {};
}

uint32_t ChunkBSet::getBlockIndex(const BlockInChunkPos &pos) const
{
    return {};
}

BlockInChunkPos ChunkBSet::getBlockPosition(uint32_t index) const
{
    return {};
}

const BlockData &ChunkBSet::getBlockData(const BlockInChunkPos &pos) const
{
    return data_;
}

Layer ChunkBSet::getLayer() const
{
    return layer_;
}

ChunkBSet::Iterator ChunkBSet::begin() const
{
    return {};
}

ChunkBSet::Iterator ChunkBSet::end() const
{
    return {};
}
