#ifndef MODBASE_ICHUNKRANGE_HPP
#define MODBASE_ICHUNKRANGE_HPP

#include <memory>
#include <array>
#include "Position.hpp"
#include <array>
#include <cstdint>

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
				/// Возвращает блок, который заполняет этот диапазон
				virtual std::shared_ptr<const object::IBlock> getBlock() const = 0;
				/* \brief Получает границы диапазона блоков в чанке
				 * \return Возвращает координаты диапазона чанка
				 * \see BoundsSize
				*/
				virtual const std::array<BlockInChunkPos, BoundsSize> &getBounds() const = 0;
				/// Возвращает количество заполняемых блоков в диапазоне
				virtual uint32_t getBlockCount() const = 0;
			protected:
				explicit IChunkRange() = default;
				virtual ~IChunkRange() = default;
			};
		}
	}
}

#endif // MODBASE_ICHUNKRANGE_HPP
