#ifndef MODBASE_POSITION_HPP
#define MODBASE_POSITION_HPP

#include <type_traits>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			template <typename TPosType>
			struct BasePos
			{
				static_assert(std::is_arithmetic<TPosType>::value, "TPosType не является арифметическим типом!");
				TPosType x;
				TPosType y;
				TPosType z;
				friend bool operator==(const BasePos &one, const BasePos &other)
				{
					return one.x == other.x
						&& one.y == other.y
						&& one.z == other.z;
				}
			};

			/*Позиция блока в чанке */
			using BlockInChunkPos = BasePos<uint8_t>;
			/*Позиция чанка в мире */
			using ChunkPos = BasePos<int64_t>;
			/*Глобальная позиция блока*/
			using BlockGlobalPos = BasePos<int64_t>;

			/* Размер грани чанка */
			constexpr uint8_t ChunkSize = 16;
		}
	}
}

#endif // MODBASE_POSITION_HPP
