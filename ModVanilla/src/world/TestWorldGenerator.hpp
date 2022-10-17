#pragma once

#include <world/IWorldGenerator.hpp>

namespace CubA4
{
	namespace world
	{
		class TestWorldGenerator :
			public virtual CubA4::mod::world::IWorldGenerator
		{
		public:
			explicit TestWorldGenerator();
			~TestWorldGenerator();

			void generateChunk(std::shared_ptr<CubA4::mod::world::IWorld> world, const CubA4::core::world::ChunkPos &chunkPos) override;
		protected:
		private:
		};
	}
}

