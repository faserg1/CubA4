#pragma once

#include <world/GlobalPosition.hpp>

namespace CubA4::render::engine::world
{
	struct Ray
	{
		CubA4::world::GlobalPosition position;
		CubA4::world::BasePos<float> direction;
	};
}