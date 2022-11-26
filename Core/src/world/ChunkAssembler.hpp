#pragma once

#include <memory>
#include <world/Chunk.hpp>
#include <world/ChunkBRange.hpp>
#include <world/ChunkBSet.hpp>
#include <world/ChunkBMulti.hpp>
#include <world/ChunkBModification.hpp>

namespace CubA4::world
{
	struct ReassmebledChunkContainers
	{
		std::vector<std::shared_ptr<ChunkBRange>> ranges;
		std::vector<std::shared_ptr<ChunkBSet>> sets;
		std::vector<std::shared_ptr<ChunkBMulti>> multis;
	};

	class ChunkAssembler
	{
	public:
		explicit ChunkAssembler();
		~ChunkAssembler();

		ReassmebledChunkContainers reassmeble(std::shared_ptr<Chunk> chunk, const ChunkBModification &modification);
		std::shared_ptr<ChunkBRange> buildRange(
			std::shared_ptr<const CubA4::object::IBlock> block,
			const CubA4::world::BlockInChunkPos &start,
			const CubA4::world::BlockInChunkPos &end,
			BlockData data = {},
			CubA4::world::Layer layer = 0);
	private:
		// cache?
	};
}
