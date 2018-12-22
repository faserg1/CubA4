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
		namespace world
		{
			class IChunkRange;
		}
	}

	namespace world
	{
		class ChunkRange;

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
		protected:
		private:
			static std::vector<sChunkRanges> findAdjacent(const scIChunkRanges ranges);
			static bool isAdjacent(scIChunkRange first, scIChunkRange second);
			static bool isIntersects(scIChunkRange first, scIChunkRange second);
			static BIC minBound(const std::array<BIC, CubA4::mod::world::BoundsSize> &positions);
			static BIC maxBound(const std::array<BIC, CubA4::mod::world::BoundsSize> &positions);
			static std::array<BIC, 8> points(const BIC &min, const BIC &max);
		};
	}
}

#endif // CORE_CHUNKRANGEBUILDER_HPP
