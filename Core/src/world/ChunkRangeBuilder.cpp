#include "./ChunkRangeBuilder.hpp"
#include "./ChunkRange.hpp"
#include <algorithm>
using namespace CubA4::world;

ChunkRangeBuilder::sChunkRanges ChunkRangeBuilder::rebuildChunkRanges(scIChunkRanges ranges)
{
	sChunkRanges rebuildedRanges;
	constexpr std::pair<BlockSide, BlockSide> empty{};
	while (!ranges.empty())
	{
		struct AdjacentData
		{
			scIChunkRange adjacent;
			std::pair<BlockSide, BlockSide> type;
		};
		std::vector<AdjacentData> adjacents;
		std::vector<decltype(ranges)::iterator> toRemove;
		auto range = ranges.back();
		ranges.pop_back();
		for (auto it = ranges.begin() ; it != ranges.end(); it++)
		{
			auto type = isSameAdjacent(range, *it);
			if (type == empty)
				continue;
			adjacents.push_back(AdjacentData{*it, type});
			toRemove.push_back(it);
		}
		for (auto it : toRemove)
		{
			ranges.erase(it);
		}
		
	}
	return rebuildedRanges;
}

ChunkRangeBuilder::sChunkRange ChunkRangeBuilder::buildRange(std::shared_ptr<const CubA4::object::IBlock> block, const BIC &start, const BIC &end)
{
	return std::make_shared<ChunkRange>(block, minMaxBounds({ start, end }));
}

std::pair<BlockSide, BlockSide> ChunkRangeBuilder::isSameAdjacent(scIChunkRange first, scIChunkRange second)
{
	constexpr const std::pair<BlockSide, BlockSide> sides[] = {
		std::pair<BlockSide, BlockSide>(BlockSide::Top, BlockSide::Bottom),
		std::pair<BlockSide, BlockSide>(BlockSide::Bottom, BlockSide::Top),
		std::pair<BlockSide, BlockSide>(BlockSide::Left, BlockSide::Right),
		std::pair<BlockSide, BlockSide>(BlockSide::Right, BlockSide::Left),
		std::pair<BlockSide, BlockSide>(BlockSide::Front, BlockSide::Back),
		std::pair<BlockSide, BlockSide>(BlockSide::Back, BlockSide::Front),
	};
	for (auto &side : sides)
	{
		if (isSideAdjacent(first->getSideRect(side.first), second->getSideRect(side.second)))
			return side;
	}
	return {};
}

bool ChunkRangeBuilder::isSideAdjacent(const IChunkRange::Bounds &s1, const IChunkRange::Bounds &s2)
{
	constexpr uint8_t x = 0x1;
	constexpr uint8_t y = 0x2;
	constexpr uint8_t z = 0x4;
	constexpr uint8_t all = x | y | z;
	uint8_t p1 = 0, p2 = 0;
	p1 |= s1[0].x == s2[0].x ? x : 0;
	p1 |= s1[0].y == s2[0].y ? y : 0;
	p1 |= s1[0].z == s2[0].z ? z : 0;

	p2 |= s1[1].x == s2[1].x ? x : 0;
	p2 |= s1[1].y == s2[1].y ? y : 0;
	p2 |= s1[1].z == s2[1].z ? z : 0;

	return p1 == p2 && p1 >= 3 && p1 != all;
}

std::array<BlockInChunkPos, MinMaxBoundsSize> ChunkRangeBuilder::minMaxBounds(const std::array<BlockInChunkPos, BoundsSize> &positions)
{
	static_assert(MinMaxBoundsSize == 2, "Количество точек для минимальной/максимальной границы должно равнятся двум.");
	std::array<BlockInChunkPos, MinMaxBoundsSize> bounds;
	bounds[MinIndex] = minBound(positions);
	bounds[MaxIndex] = maxBound(positions);
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
