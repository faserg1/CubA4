#include "./ChunkRange.hpp"
#include <string.h>
#include <cmath>
using namespace CubA4::world;
using namespace CubA4::mod::object;
using namespace CubA4::mod::world;

ChunkRange::ChunkRange(std::shared_ptr<const IBlock> block, const BlockInChunkPos *bounds) :
	block_(block)
{
	memcpy(bounds_, bounds, sizeof(BlockInChunkPos) * BoundsSize);
}

ChunkRange::~ChunkRange()
{
	
}

std::shared_ptr<const IBlock> ChunkRange::getBlock() const
{
	return block_;
}

const BlockInChunkPos *ChunkRange::getBounds() const
{
	return bounds_;
}

std::shared_ptr<const IChunkRange> ChunkRange::mergeWith(std::shared_ptr<const IChunkRange> range) const
{
	if (range->getBlock() != block_)
		return {};
	const auto *inPositions = range->getBounds();
	const auto *myPositions = getBounds();
	BlockInChunkPos outPositions[BoundsSize];
	
	auto minIn = minBound(inPositions);
	auto maxIn = maxBound(inPositions);
	auto minMy = minBound(myPositions);
	auto maxMy = maxBound(myPositions);
	
	return std::make_shared<ChunkRange>(block_, outPositions);
}

BlockInChunkPos ChunkRange::minBound(BlockInChunkPos *pos)
{
	BlockInChunkPos bound;
	bound.x = min(pos[0].x, pos[1].x);
	bound.y = min(pos[0].y, pos[1].y);
	bound.z = min(pos[0].z, pos[1].z);
	return bound;
}

BlockInChunkPos ChunkRange::maxBound(BlockInChunkPos *pos)
{
	BlockInChunkPos bound;
	bound.x = max(pos[0].x, pos[1].x);
	bound.y = max(pos[0].y, pos[1].y);
	bound.z = max(pos[0].z, pos[1].z);
	return bound;
}
