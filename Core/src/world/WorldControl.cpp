#include <world/WorldControl.hpp>
using namespace CubA4::world;

WorldControl::WorldControl(Core &core) :
	core_(core), chunkAssembler_(std::make_unique<ChunkAssembler>(*core.getEnvironment()))
{

}

void WorldControl::requestChanges(const ChunkModificationCollection& modifications, const std::string &targetDimension)
{
	auto dimension = currentWorld_->findDimension(targetDimension);

	std::vector<std::pair<std::shared_ptr<Chunk>, const ChunkBModification&>> changes;
	
	for (const auto& mod : modifications)
	{
		auto chunk = dimension->findChunk(mod.pos);
		if (!testLocal(chunk, mod))
		{
			// Return local incorrect result
			return;
		}
		changes.push_back(std::make_pair(chunk, mod));
	}
	for (auto [chunk, mod] : changes)
	{
		chunkAssembler_->applyChanges(chunk, mod);
	}
}

void WorldControl::setCurrentWorld(std::shared_ptr<World> world)
{
	currentWorld_ = world;
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