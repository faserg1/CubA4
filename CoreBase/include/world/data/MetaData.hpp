#pragma once

#include <compare>

namespace CubA4::world
{
	struct MetaData
	{
		constexpr friend std::strong_ordering operator<=>(const MetaData& a, const MetaData &b)
		{
			return std::strong_ordering::equal;
		}
	};
}
