#pragma once

#include <world/IWorldGenerator.hpp>
#include <manager/ModBlockManager.hpp>

namespace CubA4
{
	class ICore;
}

namespace CubA4::world
{
	class TestWorldGenerator :
		public virtual CubA4::world::IWorldGenerator
	{
	public:
		explicit TestWorldGenerator(const CubA4::ICore &core, const manager::ModBlockManager &blockManager);
		~TestWorldGenerator();

		ChunkBGeneration generateChunk(std::shared_ptr<CubA4::world::IWorld> world, std::shared_ptr<CubA4::world::IDimension> dimension,
			const CubA4::world::ChunkPos &chunkPos) override;
	protected:
	private:
		const CubA4::ICore &core_;
		const manager::ModBlockManager &blockManager_;
	};
}

