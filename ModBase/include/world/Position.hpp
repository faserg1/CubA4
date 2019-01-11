#ifndef MODBASE_POSITION_HPP
#define MODBASE_POSITION_HPP

#include <type_traits>
#include <cstdint>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			namespace
			{
				template <typename T>
				constexpr T ipow(T num, unsigned int pow)
				{
					return (pow >= sizeof(unsigned int) * 8) ? 0 :
						pow == 0 ? 1 : num * ipow(num, pow - 1);
				}
			}

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

			template <typename TPosTypeOut, typename TPosTypeIn>
			BasePos<TPosTypeOut> convertPos(BasePos<TPosTypeIn> pos)
			{
				return
				{
					static_cast<TPosTypeOut>(pos.x),
					static_cast<TPosTypeOut>(pos.y),
					static_cast<TPosTypeOut>(pos.z)
				};
			}

			/* Длинна грани чанка. (Объем чанка = длинна в кубе) */
			constexpr uint16_t ChunkSize = 64;
			static_assert(ChunkSize >= 8, "Чанк не может быть размером меньше 8.");
			static_assert(ChunkSize <= ipow(2, sizeof(decltype(BlockInChunkPos::x)) * 8), "Чанк не может привышать размер, превышающий макисмальные позиции блоков в чанке.");
		}
	}
}

#endif // MODBASE_POSITION_HPP
