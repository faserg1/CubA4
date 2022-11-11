#pragma once

#include <world/Position.hpp>
#include <world/IChunkRange.hpp>
#include <memory>
#include <vector>
#include <array>

namespace CubA4::world
{
	class ChunkRange;

	constexpr const uint8_t MinMaxBoundsSize = 2;
	constexpr const uint8_t MinIndex = 0;
	constexpr const uint8_t MaxIndex = 1;

	class ChunkRangeBuilder final
	{
	public:
		using sChunkRange = std::shared_ptr<ChunkRange>;
		using scIChunkRange = std::shared_ptr<CubA4::world::IChunkRange>;
		using sChunkRanges = std::vector<sChunkRange>;
		using scIChunkRanges = std::vector<scIChunkRange>;
		using BIC = CubA4::world::BlockInChunkPos;
		

		ChunkRangeBuilder() = delete;
		~ChunkRangeBuilder() = delete;

		static sChunkRanges rebuildChunkRanges(scIChunkRanges ranges);
		static sChunkRange buildRange(std::shared_ptr<const CubA4::object::IBlock> block, const BIC &start, const BIC &end);
	protected:
	private:
		static std::pair<BlockSide, BlockSide> isSameAdjacent(scIChunkRange first, scIChunkRange second);
		static bool isSideAdjacent(const IChunkRange::Bounds &s1, const IChunkRange::Bounds &s2);
		static std::array<BIC, MinMaxBoundsSize> minMaxBounds(const std::array<BIC, CubA4::world::BoundsSize> &positions);
		static BIC minBound(const std::array<BIC, CubA4::world::BoundsSize> &positions);
		static BIC maxBound(const std::array<BIC, CubA4::world::BoundsSize> &positions);
		static std::array<BIC, 8> points(const BIC &min, const BIC &max);
	};
}
