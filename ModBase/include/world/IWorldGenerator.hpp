#pragma once

#include <memory>
#include <world/IChunk.hpp>

namespace CubA4::world
{
	class IWorld;

	class IWorldGenerator
	{
	public:
		virtual void generateChunk(std::shared_ptr<IWorld> world, const world::ChunkPos &chunkPos) = 0;
	protected:
		explicit IWorldGenerator() = default;
		virtual ~IWorldGenerator() = default;
	private:
	};
}


