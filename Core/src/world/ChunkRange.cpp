#include "./ChunkRange.hpp"
#include <algorithm>

using namespace CubA4::world;
using namespace CubA4::mod::object;
using namespace CubA4::mod::world;

ChunkRange::ChunkRange(std::shared_ptr<const IBlock> block, std::array<BlockInChunkPos, BoundsSize> bounds) :
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

std::shared_ptr<const IChunkRange> ChunkRange::mergeWith(std::shared_ptr<const IChunkRange> range) const
{
	if (range->getBlock() != block_)
		return {};
	const auto &inPositions = range->getBounds();
	const auto &myPositions = getBounds();
	BlockInChunkPos outPositions[BoundsSize];
	
	const auto minIn = minBound(inPositions);
	const auto maxIn = maxBound(inPositions);
	const auto minMy = minBound(myPositions);
	const auto maxMy = maxBound(myPositions);

	const auto pointsIn = points(minIn, maxIn);
	const auto pointtMy = points(minMy, maxMy);


	
	return std::make_shared<ChunkRange>(block_, outPositions);
}

BlockInChunkPos ChunkRange::minBound(const std::initializer_list<BlockInChunkPos> &positions) const
{
	BlockInChunkPos bound;
	bound.x = std::min(positions, [](const auto &left, const auto &right) {return left.x < right.x; }).x;
	bound.y = std::min(positions, [](const auto &left, const auto &right) {return left.y < right.y; }).y;
	bound.z = std::min(positions, [](const auto &left, const auto &right) {return left.z < right.z; }).z;
	return bound;
}

BlockInChunkPos ChunkRange::maxBound(const std::initializer_list<BlockInChunkPos> &positions) const
{
	BlockInChunkPos bound;
	bound.x = std::max(positions, [](const auto &left, const auto &right) {return left.x > right.x; }).x;
	bound.y = std::max(positions, [](const auto &left, const auto &right) {return left.y > right.y; }).y;
	bound.z = std::max(positions, [](const auto &left, const auto &right) {return left.z > right.z; }).z;
	return bound;
}

std::array<BlockInChunkPos, 8> ChunkRange::points(const BlockInChunkPos &min, const BlockInChunkPos &max) const
{
	std::array<BlockInChunkPos, 8> coords;
	for (uint8_t i = 0, float zCounter; i < 8; i++, zCounter += 0.5)
	{
		coords[i].x = (i < 4 ? min.x  : max.x);
		coords[i].y = (i % 2 ? min.y : max.y);
		coords[i].z = (static_cast<uint8_t>(zCounter) % 2 ? min.z : max.z);
	}
	return std::move(coords);
}