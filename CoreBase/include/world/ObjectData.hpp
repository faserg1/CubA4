#pragma once

#include <world/MetaData.hpp>
#include <cstdint>
#include <functional>

namespace CubA4::world
{
	struct ObjectData
	{
		uint64_t id;
		MetaData meta;

		constexpr friend std::strong_ordering operator<=>(const ObjectData& a, const ObjectData &b)
		{
			auto metaCmp = a.meta <=> b.meta;
			if (metaCmp == std::weak_ordering::equivalent && a.id != b.id)
				return std::strong_ordering::equivalent;
			return metaCmp;
		}
	};
}
