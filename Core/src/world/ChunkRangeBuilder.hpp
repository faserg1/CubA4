#ifndef CORE_CHUNKRANGEBUILDER_HPP
#define CORE_CHUNKRANGEBUILDER_HPP

#include <world/Position.hpp>
#include <world/IChunkRange.hpp>
#include <memory>
#include <vector>
#include <array>

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IBlock;
		}

		namespace world
		{
			class IChunkRange;
		}
	}

	namespace world
	{
		class ChunkRange;

		constexpr const uint8_t MinMaxBoundsSize = 2;
		constexpr const uint8_t MinIndex = 0;
		constexpr const uint8_t MaxIndex = 1;

		class ChunkRangeBuilder final
		{
		public:
			using sChunkRange = std::shared_ptr<ChunkRange>;
			using scIChunkRange = std::shared_ptr<CubA4::mod::world::IChunkRange>;
			using sChunkRanges = std::vector<sChunkRange>;
			using scIChunkRanges = std::vector<scIChunkRange>;
			using BIC = CubA4::mod::world::BlockInChunkPos;
			

			ChunkRangeBuilder() = delete;
			~ChunkRangeBuilder() = delete;

			static sChunkRanges rebuildChunkRanges(const scIChunkRanges ranges);
			static sChunkRange buildRange(std::shared_ptr<const CubA4::mod::object::IBlock> block, const BIC &start, const BIC &end);
			static void test();
		protected:
		private:
			static sChunkRanges rebuildAdjacentRanges(const scIChunkRanges ranges);
			static std::vector<scIChunkRanges> findAdjacent(const scIChunkRanges ranges);
			static bool isAdjacent(scIChunkRange first, scIChunkRange second);
			static bool isIntersects(scIChunkRange first, scIChunkRange second);
			static std::array<BIC, MinMaxBoundsSize> minMaxBounds(const std::array<BIC, CubA4::mod::world::BoundsSize> &positions);
			static BIC minBound(const std::array<BIC, CubA4::mod::world::BoundsSize> &positions);
			static BIC maxBound(const std::array<BIC, CubA4::mod::world::BoundsSize> &positions);
			static std::array<BIC, 8> points(const BIC &min, const BIC &max);
		};
	}
}

#endif // CORE_CHUNKRANGEBUILDER_HPP
