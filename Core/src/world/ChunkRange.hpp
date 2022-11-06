#pragma once

#include <memory>
#include <world/Position.hpp>
#include <world/IChunkRange.hpp>
#include <cstdint>
#include <array>

namespace CubA4::world
{
	class ChunkRange :
		public virtual IChunkRange
	{
	public:
		explicit ChunkRange(std::shared_ptr<const object::IBlock> block,
			const std::array<BlockInChunkPos, BoundsSize> &bounds, Layer layer = 0);
		~ChunkRange();
		
		std::shared_ptr<const object::IBlock> getBlock() const override;
		const std::array<BlockInChunkPos, BoundsSize> &getBounds() const override;
		uint32_t getBlockCount() const override;
		Layer getLayer() const override;
		Iterator begin() const override;
		Iterator end() const override;
	protected:
	private:
		const std::shared_ptr<const object::IBlock> block_;
		const std::array<BlockInChunkPos, BoundsSize> bounds_;
		const Layer layer_;
	};
}
