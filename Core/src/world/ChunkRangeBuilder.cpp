#include "./ChunkRangeBuilder.hpp"
#include "./ChunkRange.hpp"
#include <algorithm>
#include <iterator>
using namespace CubA4::world;

ChunkRangeBuilder::scIChunkRanges ChunkRangeBuilder::rebuildChunkRanges(scIChunkRanges ranges)
{
	scIChunkRanges rebuildedRanges;
	constexpr const std::pair<BlockSide, BlockSide> empty{};
	std::sort(ranges.begin(), ranges.end(), [](const scIChunkRange& range1, const scIChunkRange& range2) -> bool
	{
		return range1->getBlockCount() > range2->getBlockCount();
	});
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
		if (adjacents.empty())
		{
			rebuildedRanges.push_back(range);
			continue;
		}
		std::sort(adjacents.begin(), adjacents.end(), [](const AdjacentData& data1, const AdjacentData& data2) -> bool
		{
			return data1.adjacent->getBlockCount() < data2.adjacent->getBlockCount();
		});
		const auto lastIdx = adjacents.size() - 1;
		auto bestMirrorType = std::make_pair(adjacents[lastIdx].type.second, adjacents[lastIdx].type.first);
		std::vector<BIC> bestBounds;
		const auto layer = adjacents.back().adjacent->getLayer();
		const auto block = adjacents.back().adjacent->getBlock();
		std::copy(adjacents.back().adjacent->getBounds().begin(), adjacents.back().adjacent->getBounds().end(), std::back_inserter(bestBounds));
		adjacents.pop_back();
		auto bestSecondAdj = std::find_if(adjacents.begin(), adjacents.end(), [&bestMirrorType](const AdjacentData& data) -> bool
		{
			return data.type == bestMirrorType;
		});
		if (bestSecondAdj != adjacents.end())
		{
			std::copy(bestSecondAdj->adjacent->getBounds().begin(), bestSecondAdj->adjacent->getBounds().end(), std::back_inserter(bestBounds));
			adjacents.erase(bestSecondAdj);
		}
		for (auto toReturn  : adjacents)
			ranges.push_back(toReturn.adjacent);
		auto newBounds = minMaxBounds(bestBounds);
		rebuildedRanges.push_back(buildRange(block, newBounds[0], newBounds[1], layer));
	}
	return rebuildedRanges;
}

ChunkRangeBuilder::sChunkRange ChunkRangeBuilder::buildRange(std::shared_ptr<const CubA4::object::IBlock> block, const BIC &start, const BIC &end, CubA4::world::Layer layer)
{
	return std::make_shared<ChunkRange>(block, minMaxBounds({ start, end }), layer);
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

std::array<BlockInChunkPos, MinMaxBoundsSize> ChunkRangeBuilder::minMaxBounds(const std::vector<BlockInChunkPos> &positions)
{
	static_assert(MinMaxBoundsSize == 2, "Количество точек для минимальной/максимальной границы должно равнятся двум.");
	std::array<BlockInChunkPos, MinMaxBoundsSize> bounds;
	bounds[MinIndex] = minBound(positions);
	bounds[MaxIndex] = maxBound(positions);
	return std::move(bounds);
}

BlockInChunkPos ChunkRangeBuilder::minBound(const std::vector<BlockInChunkPos> &positions)
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

BlockInChunkPos ChunkRangeBuilder::maxBound(const std::vector<BlockInChunkPos> &positions)
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
