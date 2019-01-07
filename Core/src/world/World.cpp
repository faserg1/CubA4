#include "World.hpp"
#include "Chunk.hpp"
#include <world/IWorldDefinition.hpp>
#include <world/IWorldSubscriber.hpp>
#include <algorithm>

// test
#include "ChunkRangeBuilder.hpp"

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

std::unique_ptr<CubA4::core::util::ISubscription> World::subscribe(IWorldSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

void World::test(std::shared_ptr<const CubA4::mod::object::IBlock> block)
{
	// TODO: [OOKAMI] Test chunk range feature. Delete function later
	auto chunk0 = findChunk({ 0, 0, 0 });
	chunk0->addChunkRange(ChunkRangeBuilder::buildRange(block, { 0, 0, 0 }, { 8, 4, 2 }));
	subscriptionHelper_.apply([](CubA4::mod::world::IWorldSubscriber *sub)
	{
		// TODO: [OOKAMI] А пофиг. Мир все равно должен быть перекомпилирован
	});
}

std::shared_ptr<const IWorldDefinition> World::getWorldDefinition() const
{
	return definition_;
}

std::vector<std::shared_ptr<const CubA4::mod::world::IChunk>> World::getChunks() const
{
	std::vector<std::shared_ptr<const CubA4::mod::world::IChunk>> result(loadedChunks_.size());
	std::transform(loadedChunks_.begin(), loadedChunks_.end(), result.begin(), [](auto pair) -> std::shared_ptr<const CubA4::mod::world::IChunk>
	{
		return pair.second;
	});
	return std::move(result);
}

std::shared_ptr<CubA4::world::Chunk> World::findChunk(const CubA4::mod::world::ChunkPos &chunkPos)
{
	auto it = loadedChunks_.find(chunkPos);
	if (it == loadedChunks_.end())
	{
		// TODO: [OOKAMI] Exception? We do not have to create new chunk. So it placeholder
		auto chunk = std::make_shared<Chunk>(chunkPos);
		loadedChunks_.insert(std::make_pair(chunkPos, chunk));
		return chunk;
	}
	return it->second;
}