#pragma once

#include <world/IChunkBSet.hpp>

namespace CubA4::world
{
	class ChunkBSet : public virtual IChunkBSet
	{
	public:
		explicit ChunkBSet(std::vector<BlockInChunkPos> positions, BlockData data, Layer layer = 0);
		~ChunkBSet();

		std::shared_ptr<const object::IBlock> getBlock() const override;
		uint32_t getBlockCount() const override;
		bool hasBlockAt(const world::BlockInChunkPos &pos) const override;
		uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const override;
		CubA4::world::BlockInChunkPos getBlockPosition(uint32_t index) const override;
		const BlockData &getBlockData(const world::BlockInChunkPos &pos) const override;
		Layer getLayer() const override;
		Iterator begin() const override;
		Iterator end() const override;
	private:
		std::vector<BlockInChunkPos> positions_;
		BlockData data_;
		Layer layer_;
	};
}
