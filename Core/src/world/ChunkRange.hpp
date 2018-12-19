#ifndef CORE_CHUNKRANGE_HPP
#define CORE_CHUNKRANGE_HPP

#include <memory>
#include <world/Position.hpp>
#include <world/IChunkRange.hpp>
#include <cstdint>

namespace CubA4
{
	namespace world
	{
		class ChunkRange :
			public virtual CubA4::mod::world::IChunkRange
		{
		public:
			explicit ChunkRange(std::shared_ptr<const CubA4::mod::object::IBlock> block,
				const CubA4::mod::world::BlockInChunkPos *bounds);
			~ChunkRange();
			
			std::shared_ptr<const CubA4::mod::object::IBlock> getBlock() const override;
			/* \brief Получает границы диапазона блоков в чанке
			 * \return Возвращает 3 координаты диапазона чанка
			*/
			const CubA4::mod::world::BlockInChunkPos *getBounds() const override;
			std::shared_ptr<const CubA4::mod::world::IChunkRange>
				mergeWith(std::shared_ptr<const CubA4::mod::world::IChunkRange> range) const override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::object::IBlock> block_;
			CubA4::mod::world::BlockInChunkPos bounds_[CubA4::mod::world::BoundsSize];
		private:
			CubA4::mod::world::BlockInChunkPos minBound(CubA4::mod::world::BlockInChunkPos *pos);
			CubA4::mod::world::BlockInChunkPos maxBound(CubA4::mod::world::BlockInChunkPos *pos);
		};
	}
}

#endif // CORE_CHUNKRANGE_HPP
