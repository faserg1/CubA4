#include "./ChunkRangeBuilder.hpp"
#include "./ChunkRange.hpp"
#include <algorithm>
using namespace CubA4::world;
using namespace CubA4::mod::world;

ChunkRangeBuilder::sChunkRanges ChunkRangeBuilder::rebuildChunkRanges(const scIChunkRanges ranges)
{
	sChunkRanges rebuildedRanges;
	auto adjancentRangesCollection = findAdjacent(ranges);
	for (auto adjancentRanges : adjancentRangesCollection)
	{
		auto rebuildedAdjacentRanges = rebuildAdjacentRanges(adjancentRanges);
		rebuildedRanges.insert(rebuildedRanges.end(), rebuildedAdjacentRanges.begin(), rebuildedAdjacentRanges.end());
	}
	return rebuildedRanges;
}

ChunkRangeBuilder::sChunkRange ChunkRangeBuilder::buildRange(std::shared_ptr<const CubA4::mod::object::IBlock> block, const BIC &start, const BIC &end)
{
	return std::make_shared<ChunkRange>(block, minMaxBounds({ start, end }));
}

ChunkRangeBuilder::sChunkRanges ChunkRangeBuilder::rebuildAdjacentRanges(const scIChunkRanges ranges)
{
	return {};
}

std::vector<ChunkRangeBuilder::scIChunkRanges> ChunkRangeBuilder::findAdjacent(const scIChunkRanges ranges)
{
	std::vector<ChunkRangeBuilder::scIChunkRanges> result;
	auto rangesCopy = ranges;
	for (auto itChunkRange = rangesCopy.begin(); itChunkRange != rangesCopy.end(); itChunkRange = rangesCopy.begin())
	{
		scIChunkRanges adjacentRanges;
		adjacentRanges.push_back(*itChunkRange);
		auto chunkRange = *itChunkRange;
		rangesCopy.erase(itChunkRange);
		scIChunkRanges::iterator it = rangesCopy.begin();
		do
		{
			it = std::find_if(it, rangesCopy.end(), [chunkRange](scIChunkRange testRange) -> bool
			{
				return isAdjacent(chunkRange, testRange);
			});
			if (it == rangesCopy.end())
				break;
			adjacentRanges.push_back(*it);
			it = rangesCopy.erase(it);
		} while (true);
		adjacentRanges.shrink_to_fit();
		result.push_back(adjacentRanges);
	}
	result.shrink_to_fit();
	return result;
}

bool ChunkRangeBuilder::isAdjacent(scIChunkRange first, scIChunkRange second)
{
	if (first->getBlock() != second->getBlock())
		return false;
	auto bounds1 = minMaxBounds(first->getBounds()), bounds2 = minMaxBounds(second->getBounds());
	uint8_t firstCounter = 0, secondCounter = 0;

	auto test = [](uint8_t &counter, const BlockInChunkPos &min1, const BlockInChunkPos &max2, decltype(BlockInChunkPos::x) BlockInChunkPos::*pos)
	{
		// TODO: [OOKAMI] Учитывать, когда чанк может считаться по другому
		// https://gitlab.com/DARTeam/CubA4Dev/CubA4/issues/80#note_126954698
		if (max2.*pos <= ChunkSize)
			counter += (min1.*pos <= max2.*pos + 1 ? 1 : 0);
		else if (min1.*pos > 0)
			counter += (min1.*pos - 1 <= max2.*pos ? 1 : 0);
	};

	test(firstCounter, bounds1[MinIndex], bounds2[MaxIndex], &BlockInChunkPos::x);
	test(firstCounter, bounds1[MinIndex], bounds2[MaxIndex], &BlockInChunkPos::y);
	test(firstCounter, bounds1[MinIndex], bounds2[MaxIndex], &BlockInChunkPos::z);

	test(secondCounter, bounds2[MinIndex], bounds1[MaxIndex], &BlockInChunkPos::x);
	test(secondCounter, bounds2[MinIndex], bounds1[MaxIndex], &BlockInChunkPos::y);
	test(secondCounter, bounds2[MinIndex], bounds1[MaxIndex], &BlockInChunkPos::z);

	return firstCounter > 1 && secondCounter > 1;
}

bool ChunkRangeBuilder::isIntersects(scIChunkRange first, scIChunkRange second)
{
	if (first->getBlock() != second->getBlock())
		return false;
	auto bounds1 = minMaxBounds(first->getBounds()), bounds2 = minMaxBounds(second->getBounds());
	uint8_t firstCounter = 0, secondCounter = 0;

	auto test = [](uint8_t &counter, const BlockInChunkPos &min1, const BlockInChunkPos &max2, decltype(BlockInChunkPos::x) BlockInChunkPos::*pos)
	{
		counter += (min1.*pos <= max2.*pos ? 1 : 0);
	};

	test(firstCounter, bounds1[MinIndex], bounds2[MaxIndex], &BlockInChunkPos::x);
	test(firstCounter, bounds1[MinIndex], bounds2[MaxIndex], &BlockInChunkPos::y);
	test(firstCounter, bounds1[MinIndex], bounds2[MaxIndex], &BlockInChunkPos::z);

	test(secondCounter, bounds2[MinIndex], bounds1[MaxIndex], &BlockInChunkPos::x);
	test(secondCounter, bounds2[MinIndex], bounds1[MaxIndex], &BlockInChunkPos::y);
	test(secondCounter, bounds2[MinIndex], bounds1[MaxIndex], &BlockInChunkPos::z);

	return firstCounter > 1 && secondCounter > 1;
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

void ChunkRangeBuilder::test()
{
	std::array<BIC, CubA4::mod::world::BoundsSize> minMax1 =
	{
		BIC {4, 4, 4},
		BIC {0, 0, 0}
	}, minMax2 = 
	{
		BIC {7, 7, 7},
		BIC {3, 3, 3}
	}, minMax3 =
	{
		BIC {0, 0, 0},
		BIC {5, 5, 5}
	}, minMax4 =
	{
		BIC {3, 6, 8},
		BIC {14, 14, 14}
	}, minMax5 = 
	{
		BIC {0, 0, 0},
		BIC {1, 1, 1}
	}, minMax6 =
	{
		BIC {1, 1, 2},
		BIC {2, 2, 2}
	}, minMax7 =
	{
		BIC {3, 3, 2},
		BIC {4, 4, 4}
	}, minMax8 =
	{
		BIC {3, 6, 8},
		BIC {14, 14, 14}
	}, minMax9 =
	{
		BIC {3, 6, 8},
		BIC {14, 14, 14}
	}, minMax10 =
	{
		BIC {3, 6, 8},
		BIC {14, 14, 14}
	};
	auto cr1 = std::make_shared<ChunkRange>(nullptr, minMax3);
	auto cr2 = std::make_shared<ChunkRange>(nullptr, minMax4);

	auto result = isAdjacent(cr1, cr2);
	auto result2 = isIntersects(cr1, cr2);

	auto cr3 = std::make_shared<ChunkRange>(nullptr, minMax5);
	auto cr4 = std::make_shared<ChunkRange>(nullptr, minMax6);
	auto cr5 = std::make_shared<ChunkRange>(nullptr, minMax7);

	auto adj = findAdjacent({ cr3, cr4, cr5 });
	auto size = adj.size();
}

static int testThings()
{
	ChunkRangeBuilder::test();
	return 0;
}

int j = testThings();