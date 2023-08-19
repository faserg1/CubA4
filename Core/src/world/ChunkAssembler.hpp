#pragma once

#include <memory>
#include <world/Chunk.hpp>
#include <world/containers/ChunkBMutable.hpp>
#include <world/ChunkBModification.hpp>
#include <world/ChunkBGeneration.hpp>
#include <core/IEnvironment.hpp>

namespace CubA4::world
{

	constexpr const uint8_t MinMaxBoundsSize = 2;

	class ChunkAssembler
	{
	public:
		explicit ChunkAssembler(CubA4::core::IEnvironment &env);
		~ChunkAssembler();

		void applyChanges(std::shared_ptr<Chunk> chunk, const ChunkBModification &mod);
		std::shared_ptr<Chunk> createChunk(const ChunkBGeneration &gen);
	private:
		static uint8_t countAdjancentBlocks(CubA4::world::BlockInChunkPos start, std::function<bool(CubA4::world::BlockInChunkPos)> checker);
		static uint8_t countAdjancentWithCornersBlocks(CubA4::world::BlockInChunkPos start, std::function<bool(CubA4::world::BlockInChunkPos)> checker);
		static std::array<CubA4::world::BlockInChunkPos, MinMaxBoundsSize> minMaxBounds(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static CubA4::world::BlockInChunkPos minBound(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static CubA4::world::BlockInChunkPos maxBound(const std::vector<CubA4::world::BlockInChunkPos> &positions);
		static std::array<CubA4::world::BlockInChunkPos, 8> points(const CubA4::world::BlockInChunkPos &min, const CubA4::world::BlockInChunkPos &max);
	private:
		// cache?

		CubA4::core::IEnvironment &env_;
	};
}
