#pragma once

#include <memory>
#include <world/Chunk.hpp>
#include <world/ChunkBRange.hpp>
#include <world/ChunkBSet.hpp>
#include <world/ChunkBMulti.hpp>
#include <world/ChunkBMutable.hpp>
#include <world/ChunkBModification.hpp>
#include <system/IEnvironment.hpp>

namespace CubA4::world
{
	struct ReassembledChunkContainers
	{
		std::vector<std::shared_ptr<ChunkBRange>> addedRanges;
		std::vector<std::shared_ptr<ChunkBSet>> addedSets;
		std::vector<std::shared_ptr<ChunkBMulti>> addedMultis;
		std::vector<std::shared_ptr<ChunkBMutable>> addedMutable;

		// mutable mutated?

		std::vector<std::shared_ptr<const IChunkBBaseContainer>> removed;

		ReassembledChunkContainers &operator+=(const ReassembledChunkContainers &other);
	};

	constexpr const uint8_t MinMaxBoundsSize = 2;

	class ChunkAssembler
	{
	public:
		explicit ChunkAssembler(CubA4::system::IEnvironment &env);
		~ChunkAssembler();

		ReassembledChunkContainers reassemble(std::shared_ptr<Chunk> chunk, const ChunkBModification &modification);
		static std::shared_ptr<ChunkBRange> buildRange(
			size_t id,
			std::shared_ptr<const CubA4::object::IBlock> block,
			const CubA4::world::BlockInChunkPos &start,
			const CubA4::world::BlockInChunkPos &end,
			BlockData data = {},
			CubA4::world::Layer layer = 0);
	private:
		ReassembledChunkContainers reassembleByBlock(std::shared_ptr<Chunk> chunk, std::shared_ptr<const CubA4::object::IBlock> block, const ChunkBModification &modification);
		ReassembledChunkContainers reassembleByBlockData(std::shared_ptr<Chunk> chunk, std::shared_ptr<const CubA4::object::IBlock> block, BlockData data, const ChunkBModification &modification);

		static std::array<CubA4::world::BlockInChunkPos, MinMaxBoundsSize> minMaxBounds(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static CubA4::world::BlockInChunkPos minBound(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static CubA4::world::BlockInChunkPos maxBound(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static std::array<CubA4::world::BlockInChunkPos, 8> points(const CubA4::world::BlockInChunkPos &min, const CubA4::world::BlockInChunkPos &max);
	private:
		// cache?

		CubA4::system::IEnvironment &env_;
	};
}
