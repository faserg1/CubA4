#pragma once

#include <cstdint>
#include <util/Enums.hpp>

namespace CubA4
{
	/// @brief Define the mode application should work
	/// If it use
	enum class ApplicationModeFlag : uint8_t
	{
		None = 0x0,
		Master = 0x1,
	};

	CUBA4_ENUM_FLAGS_OPERATORS(ApplicationModeFlag, ApplicationModeFlags, uint8_t)
}

