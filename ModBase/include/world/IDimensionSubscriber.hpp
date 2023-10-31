#pragma once

#include <world/Position.hpp>

namespace CubA4::world
{
	class IDimensionSubscriber
	{
	public:
		virtual void onActiveChunksUpdated() {}
		virtual void onLoadedChunksUpdated() {}
		virtual void onChunkUpdated(const CubA4::world::ChunkPos &chunkPos) {}
	protected:
		explicit IDimensionSubscriber() = default;
		virtual ~IDimensionSubscriber() = default;
	};
}
