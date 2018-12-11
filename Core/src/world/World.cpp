#include "World.hpp"
#include "Chunk.hpp"
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

std::unique_ptr<CubA4::core::util::ISubscription> World::subscribe(IWorldSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

std::shared_ptr<const IWorldDefinition> World::getWorldDefinition() const
{
	return definition_;
}

void World::placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, const std::vector<BlockGlobalPos> positions)
{
	CubA4::mod::world::ChunkPos chunkPos;
	CubA4::mod::world::BlockInChunkPos blockPos;
	std::unordered_map<const CubA4::mod::world::ChunkPos, std::vector<CubA4::mod::world::BlockInChunkPos>, CubA4::core::util::ChunkPosHash> resolvedPositions;
	for (const auto &pos : positions)
	{
		resolve(pos, chunkPos, blockPos);
		auto it = resolvedPositions.find(chunkPos);
		if (it == resolvedPositions.end())
			resolvedPositions.insert(std::make_pair(chunkPos, std::vector<CubA4::mod::world::BlockInChunkPos>{blockPos}));
		else
			it->second.push_back(blockPos);
	}
	for (auto &resolvedPosition : resolvedPositions)
	{
		auto chunk = findChunk(resolvedPosition.first);
		if (!chunk)
		{
			// TODO: [OOKAMI] Chunk has not loaded? Not found? Why?
			continue;
		}
		chunk->placeBlocks(block, resolvedPosition.second);
	}
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

void World::resolve(const CubA4::mod::world::BlockGlobalPos &globalPos, CubA4::mod::world::ChunkPos &chunkPos, CubA4::mod::world::BlockInChunkPos &blockPos)
{
	blockPos.x = globalPos.x % ChunkSize;
	blockPos.y = globalPos.y % ChunkSize;
	blockPos.z = globalPos.z % ChunkSize;
	
	chunkPos.x = (globalPos.x - blockPos.x) / ChunkSize;
	chunkPos.y = (globalPos.y - blockPos.y) / ChunkSize;
	chunkPos.z = (globalPos.z - blockPos.z) / ChunkSize;
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