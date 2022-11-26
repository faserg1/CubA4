#pragma once

#include <world/IChunkBUnion.hpp>
#include <array>

namespace CubA4::world
{
	class IChunkBRange : public IChunkBUnion
	{
	public:
		using Bounds = std::array<world::BlockInChunkPos, BoundsSize>;
	public:
		virtual ~IChunkBRange() = default;
		ChunkBContainerType getType() const override final { return ChunkBContainerType::Range; }

		/*\brief Получает границы диапазона блоков в чанке
		* \return Возвращает координаты диапазона чанка
		* \see BoundsSize
		*/
		virtual const Bounds &getBounds() const = 0;
		virtual Bounds getSideRect(BlockSide side) const = 0;
	protected:
		explicit IChunkBRange() = default;
	};
}
