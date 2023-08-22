#include "./TestWorldGenerator.hpp"
#include <ICore.hpp>
using namespace CubA4::world;

TestWorldGenerator::TestWorldGenerator(const CubA4::ICore &core, const manager::ModBlockManager &blockManager) :
	core_(core), blockManager_(blockManager)
{
	srand(231231241);
}

TestWorldGenerator::~TestWorldGenerator()
{
	
}

ChunkBGeneration TestWorldGenerator::generateChunk(std::shared_ptr<IWorld> world, std::shared_ptr<CubA4::world::IDimension> dimension, const ChunkPos &chunkPos)
{
	auto block1 = blockManager_.getBlock("testBlock1");
	auto block2 = blockManager_.getBlock("testBlock2");
	auto simpleData = std::make_shared<BlockData>();
	auto env = core_.getEnvironment();
	auto id1 = env->getId(block1);
	auto id2 = env->getId(block2);
	ChunkBGeneration gen;
	gen.pos = chunkPos;
	auto &lit = gen.layers.emplace_back();
	lit.add.emplace_back();
	lit.add.emplace_back();

	auto &addInfo1 = lit.add[0];
	auto &addInfo2 = lit.add[1];

	addInfo1.info.blockId = id1;
	addInfo1.info.data = simpleData;
	addInfo1.positions.reserve(ChunkSize * ChunkSize);
	
	addInfo2.info.blockId = id2;
	addInfo2.info.data = simpleData;
	addInfo2.positions.reserve(ChunkSize * ChunkSize * 2);
	
	for (decltype(BlockInChunkPos::x) x = 0; x < ChunkSize; ++x)
	{
		for (decltype(BlockInChunkPos::z) z = 0; z < ChunkSize; ++z)
		{
			addInfo1.positions.push_back({x, ChunkSize - 4, z});
			addInfo2.positions.push_back({x, ChunkSize - 3, z});
			if (rand() % 3 == 0)
				addInfo2.positions.push_back({x, ChunkSize - 2, z});
			if (rand() % 5 == 0)
				addInfo2.positions.push_back({x, ChunkSize - 1, z});
		}
	}
	return gen;
}