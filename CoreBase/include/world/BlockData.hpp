#pragma once

#include <world/ObjectData.hpp>
#include <world/Position.hpp>

namespace CubA4::world
{
	struct BlockData : ObjectData
	{

	};

	struct PosBlockData : BlockData
	{
		ChunkPos chunkPos;
		BlockInChunkPos pos;
		Layer layer;
	};
}
