#pragma once

#include <cstdint>
#include <util/Enums.hpp>

namespace CubA4::object
{
	enum class TickType : uint8_t
	{
		None = 0x0,
		GameTick = 0x1,
		PhysicsTick = 0x2,
		RenderTick = 0x4
	};

	CUBA4_ENUM_FLAGS_OPERATORS(TickType, TickTypes, uint8_t)
}