#include "World.hpp"
#include <world/IWorldDefinition.hpp>
#include <world/IWorldSubscriber.hpp>
#include <algorithm>
using namespace CubA4::world;
using namespace CubA4::mod::world;

World::World(std::shared_ptr<const IWorldDefinition> definition) :
	definition_(definition)
{
	
}

World::~World()
{
	
}

std::string World::getId() const
{
	return definition_->getId();
}

std::wstring World::getName() const
{
	return definition_->getName();
}

void World::subscribe(IWorldSubscriber *subscriber)
{
	subscribers_.push_back(subscriber);
}

void World::unsubscribe(IWorldSubscriber *subscriber)
{
	std::remove(subscribers_.begin(), subscribers_.end(), subscriber);
}

std::shared_ptr<const IWorldDefinition> World::getWorldDefinition() const
{
	return definition_;
}

void World::placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, std::vector<BlockGlobalPos> positions)
{

}

void World::resolve(const CubA4::mod::world::BlockGlobalPos &globalPos, CubA4::mod::world::ChunkPos &chunkPos, CubA4::mod::world::BlockInChunkPos &blockPos)
{
	blockPos.x = globalPos.x % ChunkSize;
	blockPos.y = globalPos.y % ChunkSize;
	blockPos.z = globalPos.z % ChunkSize;
	
	chunkPos.x = (globalPos.x - blockPos.x) / ChunkSize;
	chunkPos.y = (globalPos.y - blockPos.y) / ChunkSize;
	chunkPos.z = (globalPos.z - blockPos.z) / ChunkSize;
}