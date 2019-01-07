#ifndef CORE_CHUNKRANGE_HPP
#define CORE_CHUNKRANGE_HPP

#include <memory>
#include <world/Position.hpp>
#include <world/IChunkRange.hpp>
#include <cstdint>
#include <array>

namespace CubA4
{
	namespace world
	{
		class ChunkRange :
			public virtual CubA4::mod::world::IChunkRange
		{
		public:
			explicit ChunkRange(std::shared_ptr<const CubA4::mod::object::IBlock> block,
				const std::array<CubA4::mod::world::BlockInChunkPos, CubA4::mod::world::BoundsSize> &bounds);
			~ChunkRange();
			
			std::shared_ptr<const CubA4::mod::object::IBlock> getBlock() const override;
			const std::array<CubA4::mod::world::BlockInChunkPos, CubA4::mod::world::BoundsSize> &getBounds() const override;
			uint32_t getBlockCount() const override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::object::IBlock> block_;
			const std::array<CubA4::mod::world::BlockInChunkPos, CubA4::mod::world::BoundsSize> bounds_;
		};
	}
}

#endif // CORE_CHUNKRANGE_HPP
