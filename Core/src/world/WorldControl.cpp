#include <world/WorldControl.hpp>
#include <world/IDimensionDescription.hpp>
using namespace CubA4::world;

WorldControl::WorldControl(Core &core) :
	core_(core), chunkAssembler_(std::make_unique<ChunkAssembler>(*core.getEnvironment()))
{

}

void WorldControl::requestChanges(const ChunkModificationCollection& modifications, const std::string &targetDimension)
{
	auto dimension = currentWorld_->findDimension(targetDimension);

	// TODO: ???
	if (!dimension)
		return;

	std::vector<std::pair<std::shared_ptr<Chunk>, const ChunkBModification>> changes;
	
	for (const auto& mod : modifications)
	{
		auto chunk = dimension->findChunk(mod.pos);
		// TODO: ???
		if (!chunk)
			continue;
		if (!testLocal(chunk, mod))
		{
			// Return local incorrect result
			return;
		}
		auto pair = std::make_pair(chunk, mod);
		changes.push_back(pair);
	}
	for (const auto &[chunk, mod] : changes)
	{
		chunkAssembler_->applyChanges(chunk, mod);
		dimension->subscriptionHelper_.apply([chunkPos = chunk->getChunkPos()](auto *subscriber)
		{
			subscriber->onChunkUpdated(chunkPos);
		});
	}
}

bool WorldControl::setCurrentWorld(std::shared_ptr<World> world)
{
	if (currentWorld_ == world)
		return false;
	currentWorld_ = world;
	return true;
}

bool WorldControl::setCurrentDimension(std::shared_ptr<Dimension> dimension)
{
	if (currentDimension_ == dimension)
		return false;
	currentDimension_ = dimension;
	// Load or generate chunks
	generate(dimension);
	return true;
}

std::shared_ptr<IWorld> WorldControl::getCurrentWorld()
{
	return currentWorld_;
}

std::shared_ptr<const IWorld> WorldControl::getCurrentWorld() const
{
	return currentWorld_;
}

bool WorldControl::testLocal(std::shared_ptr<Chunk> chunk, const ChunkBModification& modification) const
{
	// TODO: implement
	return true;
}

void WorldControl::generate(std::shared_ptr<Dimension> dimension)
{
	auto generator = dimension->getDimensionDescription().getWorldGenerator();
	// test implementation
	for (decltype(ChunkPos::x) x = -3; x < 4; ++x)
	{
		for (decltype(ChunkPos::z) z = -3; z < 4; ++z)
		{
			auto chunkPos = ChunkPos {x, -1, z};
			auto genInfo = generator->generateChunk(currentWorld_, dimension, chunkPos);
			auto chunk = chunkAssembler_->createChunk(genInfo);
			dimension->onChunkLoaded(chunk);
		}
	}
	dimension->subscriptionHelper_.apply([](auto *subscriber)
	{
		subscriber->onLoadedChunksUpdated();
	});
}