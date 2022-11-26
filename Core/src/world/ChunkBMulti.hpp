#pragma once

#include <world/IChunkBMulti.hpp>

namespace CubA4::world
{
	class ChunkBMulti : public virtual IChunkBMulti
	{
	public:
		explicit ChunkBMulti();
		~ChunkBMulti();
	};
}
