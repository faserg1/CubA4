#pragma once

#include <memory>
#include <world/IChunk.hpp>
#include <world/IWorldGeneratorData.hpp>
#include <world/ChunkBGeneration.hpp>

namespace CubA4::world
{
	class IWorld;
	class IDimension;

	class IWorldGenerator
	{
	public:
		virtual ChunkBGeneration generateChunk(std::shared_ptr<IWorld> world, std::shared_ptr<IDimension> dimension, const world::ChunkPos &chunkPos) = 0;
	protected:
		explicit IWorldGenerator() = default;
		virtual ~IWorldGenerator() = default;
	private:
		// data
	};
}


