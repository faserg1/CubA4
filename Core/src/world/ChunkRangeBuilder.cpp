#include "./ChunkRangeBuilder.hpp"
#include "./ChunkRange.hpp"
#include <algorithm>
using namespace CubA4::world;
using namespace CubA4::mod::world;

ChunkRangeBuilder::sChunkRanges ChunkRangeBuilder::rebuildChunkRanges(const scIChunkRanges ranges)
{
	return {};
}

std::vector<ChunkRangeBuilder::sChunkRanges> ChunkRangeBuilder::findAdjacent(const scIChunkRanges ranges)
{
	return {};
}

bool ChunkRangeBuilder::isAdjacent(scIChunkRange first, scIChunkRange second)
{
	return false;
}

bool ChunkRangeBuilder::isIntersects(scIChunkRange first, scIChunkRange second)
{
	if (first->getBlock() != second->getBlock())
		return false;
	auto bounds1 = minMaxBounds(first->getBounds()), bounds2 = minMaxBounds(second->getBounds());

	return false;
}

std::array<BlockInChunkPos, MinMaxBoundsSize> ChunkRangeBuilder::minMaxBounds(const std::array<BlockInChunkPos, BoundsSize> &positions)
{
	static_assert(MinMaxBoundsSize == 2, "Количество точек для минимальной/максимальной границы должно равнятся двум.");
	std::array<BlockInChunkPos, MinMaxBoundsSize> bounds;
	bounds[0] = minBound(positions);
	bounds[1] = maxBound(positions);
	return std::move(bounds);
}

BlockInChunkPos ChunkRangeBuilder::minBound(const std::array<BlockInChunkPos, BoundsSize> &positions)
{
	BlockInChunkPos bound;
	auto find_min = [&positions, &bound](decltype(BlockInChunkPos::x) BlockInChunkPos::*coord)
	{
		bound.*coord = (*std::min_element(positions.begin(), positions.end(), [&coord](const auto &left, const auto &right) {return left.*coord < right.*coord; })).*coord;
	};
	find_min(&BlockInChunkPos::x);
	find_min(&BlockInChunkPos::y);
	find_min(&BlockInChunkPos::z);
	return bound;
}

BlockInChunkPos ChunkRangeBuilder::maxBound(const std::array<BlockInChunkPos, BoundsSize> &positions)
{
	BlockInChunkPos bound;
	auto find_max = [&positions, &bound](decltype(BlockInChunkPos::x) BlockInChunkPos::*coord)
	{
		bound.*coord = (*std::max_element(positions.begin(), positions.end(), [&coord](const auto &left, const auto &right) {return left.*coord < right.*coord; })).*coord;
	};
	find_max(&BlockInChunkPos::x);
	find_max(&BlockInChunkPos::y);
	find_max(&BlockInChunkPos::z);
	return bound;
}

std::array<BlockInChunkPos, 8> ChunkRangeBuilder::points(const BlockInChunkPos &min, const BlockInChunkPos &max)
{
	std::array<BlockInChunkPos, 8> coords;
	float zCounter = 0;
	for (uint8_t i = 0; i < 8; i++, zCounter += 0.5)
	{
		coords[i].x = (i < 4 ? min.x : max.x);
		coords[i].y = (i % 2 ? min.y : max.y);
		coords[i].z = (static_cast<uint8_t>(zCounter) % 2 ? min.z : max.z);
	}
	return std::move(coords);
}