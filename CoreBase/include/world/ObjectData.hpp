#pragma once

#include <world/MetaData.hpp>
#include <cstdint>

namespace CubA4::world
{
	struct ObjectData
	{
		uint64_t id;
		MetaData meta;
	};
}
