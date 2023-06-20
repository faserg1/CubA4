#pragma once

#include <util/Enums.hpp>
#include <cstdint>

namespace CubA4::world
{
	/**
	 * @brief Стороны света
	 */
	enum class Side
	{
		North = 0,
		South = 1,
		East = 2,
		West = 3
	};

	/**
	 * @brief Стороны блока
	 * 
	 */
	enum class BlockSide : uint8_t
	{
		Top = 0x1,
		Bottom = 0x2,
		Front = 0x4,
		Back = 0x8,
		Left = 0x10,
		Right = 0x20
	};

	CUBA4_ENUM_FLAGS_OPERATORS(BlockSide, BlockSides, uint8_t)

	constexpr const BlockSides AllSides = BlockSide::Top | BlockSide::Bottom | BlockSide::Front | BlockSide::Back | BlockSide::Left | BlockSide::Right;
}
