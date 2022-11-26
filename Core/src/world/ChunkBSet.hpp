#pragma once

#include <world/IChunkBSet.hpp>

namespace CubA4::world
{
	class ChunkBSet : public virtual IChunkBSet
	{
	public:
		explicit ChunkBSet();
		~ChunkBSet();
	};
}
