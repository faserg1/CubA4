#pragma once

#include <world/IWorldGenerator.hpp>

namespace CubA4
{
	namespace world
	{
		class TestWorldGenerator :
			public virtual CubA4::world::IWorldGenerator
		{
		public:
			explicit TestWorldGenerator();
			~TestWorldGenerator();

			void generateChunk(std::shared_ptr<CubA4::world::IWorld> world, const CubA4::world::ChunkPos &chunkPos) override;
		protected:
		private:
		};
	}
}

