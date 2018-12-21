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
				std::array<CubA4::mod::world::BlockInChunkPos, CubA4::mod::world::BoundsSize> bounds);
			~ChunkRange();
			
			std::shared_ptr<const CubA4::mod::object::IBlock> getBlock() const override;
			/* \brief Получает границы диапазона блоков в чанке
			 * \return Возвращает 3 координаты диапазона чанка
			*/
			const std::array<CubA4::mod::world::BlockInChunkPos, CubA4::mod::world::BoundsSize> &getBounds() const override;
			std::shared_ptr<const CubA4::mod::world::IChunkRange>
				mergeWith(std::shared_ptr<const CubA4::mod::world::IChunkRange> range) const override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::object::IBlock> block_;
			const std::array<CubA4::mod::world::BlockInChunkPos, CubA4::mod::world::BoundsSize> bounds_;
		private:
			CubA4::mod::world::BlockInChunkPos minBound(const std::initializer_list<CubA4::mod::world::BlockInChunkPos> &positions) const;
			CubA4::mod::world::BlockInChunkPos maxBound(const std::initializer_list<CubA4::mod::world::BlockInChunkPos> &positions) const;
			std::array<CubA4::mod::world::BlockInChunkPos, 8> points(const CubA4::mod::world::BlockInChunkPos &min, const CubA4::mod::world::BlockInChunkPos &max) const;
		};
	}
}

#endif // CORE_CHUNKRANGE_HPP
