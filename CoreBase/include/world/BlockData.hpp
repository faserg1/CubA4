#pragma once

#include <world/ObjectData.hpp>
#include <world/Position.hpp>

namespace CubA4::world
{
	struct BlockData : ObjectData
	{
		ChunkPos chunkPos;
		BlockInChunkPos pos;
	};
}
