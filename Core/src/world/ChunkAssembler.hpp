#pragma once

#include <memory>
#include <world/Chunk.hpp>
#include <world/containers/ChunkBMutable.hpp>
#include <world/ChunkBModification.hpp>
#include <system/IEnvironment.hpp>

namespace CubA4::world
{

	constexpr const uint8_t MinMaxBoundsSize = 2;

	class ChunkAssembler
	{
	public:
		explicit ChunkAssembler(CubA4::system::IEnvironment &env);
		~ChunkAssembler();

		static std::shared_ptr<IChunkBBaseContainer> buildRange(
			size_t id,
			std::shared_ptr<const CubA4::object::IBlock> block,
			const CubA4::world::BlockInChunkPos &start,
			const CubA4::world::BlockInChunkPos &end,
			decltype(BlockData::id) dataId = {},
			CubA4::world::Layer layer = 0);
	private:
		static uint8_t countAdjancentBlocks(CubA4::world::BlockInChunkPos start, std::function<bool(CubA4::world::BlockInChunkPos)> checker);
		static uint8_t countAdjancentWithCornersBlocks(CubA4::world::BlockInChunkPos start, std::function<bool(CubA4::world::BlockInChunkPos)> checker);
		static std::array<CubA4::world::BlockInChunkPos, MinMaxBoundsSize> minMaxBounds(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static CubA4::world::BlockInChunkPos minBound(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static CubA4::world::BlockInChunkPos maxBound(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static std::array<CubA4::world::BlockInChunkPos, 8> points(const CubA4::world::BlockInChunkPos &min, const CubA4::world::BlockInChunkPos &max);
	private:
		// cache?

		CubA4::system::IEnvironment &env_;
	};
}
