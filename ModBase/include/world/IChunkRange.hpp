#ifndef MODBASE_ICHUNKRANGE_HPP
#define MODBASE_ICHUNKRANGE_HPP

#include <memory>
#include "Position.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IBlock;
		}
		
		namespace world
		{
			constexpr const uint8_t BoundsSize = 2;
			
			/// Диапазон блоков в чанке
			class IChunkRange
			{
			public:
				virtual std::shared_ptr<const object::IBlock> getBlock() const = 0;
				/* \brief Получает границы диапазона блоков в чанке
				 * \return Возвращает 3 координаты диапазона чанка
				*/
				virtual const BlockInChunkPos *getBounds() const = 0;
				virtual std::shared_ptr<const IChunkRange> mergeWith(std::shared_ptr<const IChunkRange> range) const = 0;
			protected:
				explicit IChunkRange() = default;
				virtual ~IChunkRange() = default;
			};
		}
	}
}

#endif // MODBASE_ICHUNKRANGE_HPP
