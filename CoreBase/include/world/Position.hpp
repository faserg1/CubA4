#pragma once

#include <type_traits>
#include <cstdint>

namespace CubA4::world
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

		friend bool operator<(const BasePos &one, const BasePos &other)
		{
			if (one.z < other.z)
				return true;
			if (one.z > other.z)
				return false;
			if (one.y < other.y)
				return true;
			if (one.y > other.y)
				return false;
			if (one.x < other.x)
				return true;
			if (one.x > other.x)
				return false;
			return false;
		}
	};

	/*Позиция блока в чанке */
	using BlockInChunkPos = BasePos<uint8_t>;
	/*Позиция чанка в мире */
	using ChunkPos = BasePos<int32_t>;

	using Layer = uint8_t;

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

	struct BlockPosition
	{
		BlockInChunkPos position;
		Layer layer;
	};

	template <typename TPosType>
	constexpr bool isInBounds(BasePos<TPosType> min, BasePos<TPosType> max, BasePos<TPosType> check)
	{
		return min.x <= check.x && check.x <= max.x && 
			min.y <= check.y && check.y <= max.y && 
			min.z <= check.z && check.z <= max.z; 
	}

	/* Длинна грани чанка. (Объем чанка = длинна в кубе) */
	constexpr uint16_t ChunkSize = 64;
	static_assert(ChunkSize >= 8, "Чанк не может быть размером меньше 8.");
	static_assert(ChunkSize <= ipow(2, sizeof(decltype(BlockInChunkPos::x)) * 8), "Чанк не может привышать размер, превышающий макисмальные позиции блоков в чанке.");

	/// Диапазон блоков в чанке измеряется начальной минимальной точкой и конечной максимальной точкой
	constexpr const uint8_t BoundsSize = 2;
}
