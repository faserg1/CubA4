#pragma once

#include <world/IChunkBSet.hpp>

namespace CubA4::world
{
	class ChunkBSet : public virtual IChunkBSet
	{
	public:
		explicit ChunkBSet(std::shared_ptr<const object::IBlock> block, std::vector<BlockInChunkPos> positions, std::shared_ptr<BlockData> data, Layer layer = 0);
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
		class SetIterator : public virtual IChunkBIterator
		{
		public:
			SetIterator(const ChunkBSet *set, uint32_t index);
			std::unique_ptr<IChunkBIterator> copy() const override;
			bool equal(const IChunkBIterator *other) const override;
			void move(int32_t shift) override;
			const CubA4::world::BlockInChunkPos &get() const override;
		private:
			const ChunkBSet *set_;
			uint32_t index_;
			CubA4::world::BlockInChunkPos pos_;
		};
	private:
		std::shared_ptr<const object::IBlock> block_;
		std::vector<BlockInChunkPos> positions_;
		std::shared_ptr<BlockData> data_;
		Layer layer_;
	};
}
