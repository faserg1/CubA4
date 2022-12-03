#pragma once

#include <world/IChunkBRange.hpp>

namespace CubA4::world
{
	class ChunkBRange : public virtual IChunkBRange
	{
	public:
		explicit ChunkBRange(std::shared_ptr<const object::IBlock> block,
			const std::array<BlockInChunkPos, BoundsSize> &bounds, BlockData data, Layer layer = 0);
		~ChunkBRange();

		std::shared_ptr<const object::IBlock> getBlock() const override;
		const Bounds &getBounds() const override;
		Bounds getSideRect(BlockSide side) const override;
		uint32_t getBlockCount() const override;
		bool hasBlockAt(const world::BlockInChunkPos &pos) const override;
		uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const override;
		CubA4::world::BlockInChunkPos getBlockPosition(uint32_t index) const override;
		const BlockData &getBlockData(const world::BlockInChunkPos &pos) const override;
		Layer getLayer() const override;
		Iterator begin() const override;
		Iterator end() const override;
	protected:
		class RangeIterator : public virtual IChunkBIterator
		{
		public:
			RangeIterator(const ChunkBRange *range, uint32_t index);
			std::unique_ptr<IChunkBIterator> copy() const override;
			bool equal(const IChunkBIterator *other) const override;
			void move(int32_t shift) override;
			const CubA4::world::BlockInChunkPos &get() const override;
		private:
			const ChunkBRange *range_;
			uint32_t index_;
			CubA4::world::BlockInChunkPos pos_;
		};
	private:
		const std::shared_ptr<const object::IBlock> block_;
		const std::array<BlockInChunkPos, BoundsSize> bounds_;
		const BlockData data_;
		const Layer layer_;
	};
}
