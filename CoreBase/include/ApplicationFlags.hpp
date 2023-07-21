#pragma once

#include <util/Enums.hpp>
#include <cstdint>

namespace CubA4
{
	enum class ApplicationFlag : uint8_t
	{
		Default = 0x0,
		Render = 0x1,
	};

	CUBA4_ENUM_FLAGS_OPERATORS(ApplicationFlag, ApplicationFlags, uint8_t)
}

