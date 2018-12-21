#include "./ChunkRange.hpp"
#include <string.h>
#include <cmath>
using namespace CubA4::world;
using namespace CubA4::mod::object;
using namespace CubA4::mod::world;

ChunkRange::ChunkRange(std::shared_ptr<const IBlock> block,
	const std::array<BlockInChunkPos, BoundsSize> &bounds) :
	block_(block), bounds_(bounds)
{
}

ChunkRange::~ChunkRange()
{
	
}

std::shared_ptr<const IBlock> ChunkRange::getBlock() const
{
	return block_;
}

const std::array<BlockInChunkPos, BoundsSize> &ChunkRange::getBounds() const
{
	return bounds_;
}
