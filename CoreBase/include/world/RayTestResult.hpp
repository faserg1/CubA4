#pragma once

#include <world/GlobalPosition.hpp>
#include <world/Sides.hpp>

namespace CubA4::world
{
	struct RayTestResult
	{
		ChunkPos chunkPos;
		BlockInChunkPos blockPos;
		BlockSide side;
	};
}