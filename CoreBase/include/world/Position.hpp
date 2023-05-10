#pragma once

#include <type_traits>
#include <cstdint>

namespace CubA4::world
{
	/// Details
	namespace
	{
		template <typename T>
		constexpr T ipow(T num, unsigned int pow)
		{
			return (pow >= sizeof(unsigned int) * 8) ? 0 :
				pow == 0 ? 1 : num * ipow(num, pow - 1);
		}
	}

	/* Длинна грани чанка. (Объем чанка = длинна в кубе) */
	constexpr const uint16_t ChunkSize = 64;
	constexpr const uint32_t ChunkCube = ChunkSize * ChunkSize * ChunkSize;

	/// Диапазон блоков в чанке измеряется начальной минимальной точкой и конечной максимальной точкой
	constexpr const uint8_t BoundsSize = 2;

	template <typename TPosType>
	struct BasePos
	{
		static_assert(std::is_arithmetic<TPosType>::value, "TPosType не является арифметическим типом!");
		TPosType x;
		TPosType y;
		TPosType z;

		BasePos &operator+=(const BasePos &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		BasePos &operator-=(const BasePos &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		BasePos &operator*=(const TPosType val)
		{
			x *= val;
			y *= val;
			z *= val;
			return *this;
		}
		BasePos &operator/=(const TPosType val)
		{
			x /= val;
			y /= val;
			z /= val;
			return *this;
		}
		BasePos &operator=(const BasePos &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		template <typename TOtherPos>
		friend bool operator==(const BasePos &one, const BasePos<TOtherPos> &other)
		{
			return one.x == other.x
				&& one.y == other.y
				&& one.z == other.z;
		}

		template <typename TOtherPos>
		friend bool operator<(const BasePos &one, const BasePos<TOtherPos> &other)
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

		template <typename TOtherPos>
		friend BasePos operator+(const BasePos &one, const BasePos<TOtherPos> &two)
		{
			return BasePos {
				static_cast<TPosType>(one.x + two.x),
				static_cast<TPosType>(one.y + two.y),
				static_cast<TPosType>(one.z + two.z),
			};
		}

		template <typename TOtherPos>
		friend BasePos operator-(const BasePos &one, const BasePos<TOtherPos> &two)
		{
			return BasePos {
				static_cast<TPosType>(one.x - two.x),
				static_cast<TPosType>(one.y - two.y),
				static_cast<TPosType>(one.z - two.z),
			};
		}
	};

	/*Позиция блока в чанке */
	using BlockInChunkPos = BasePos<int16_t>;
	/*Позиция чанка в мире */
	using ChunkPos = BasePos<int32_t>;

	using Layer = uint8_t;

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

	constexpr size_t indexByPos(const BlockInChunkPos &pos)
	{
		return (pos.z * ChunkSize * ChunkSize) + (pos.y * ChunkSize) + pos.x;
	}

	constexpr const BasePos<int8_t> AdjancentPositions[] = {
		{-1, 0, 0},  // left
		{1, 0, 0},   // right
		{0, -1, 0},  // down
		{0, 1, 0},   // up
		{0, 0, -1},  // back
		{0, 0, 1}    // front
	};

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

	/// Static checks
	static_assert(ChunkSize >= 8, "Чанк не может быть размером меньше 8.");
	static_assert(ChunkSize <= ipow(2, sizeof(decltype(BlockInChunkPos::x)) * 8), "Чанк не может привышать размер, превышающий макисмальные позиции блоков в чанке.");
}
