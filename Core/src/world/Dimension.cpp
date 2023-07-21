#include <world/Dimension.hpp>
using namespace CubA4::world;

Dimension::Dimension(Core &core, const CubA4::world::IDimensionDescription &description) :
	core_(core), description_(description)
{

}

Dimension::IdType Dimension::getId() const
{
	return description_.getId();
}

std::wstring Dimension::getName() const
{
	return description_.getName();
}

std::unique_ptr<CubA4::util::ISubscription> Dimension::subscribe(CubA4::world::IDimensionSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

const CubA4::world::IDimensionDescription &Dimension::getDimensionDescription() const
{
	return description_;
}

std::vector<std::shared_ptr<const IChunk>> Dimension::getChunks() const
{
	std::vector<std::shared_ptr<const CubA4::world::IChunk>> result(loadedChunks_.size());
	std::transform(loadedChunks_.begin(), loadedChunks_.end(), result.begin(), [](auto pair) -> std::shared_ptr<const CubA4::world::IChunk>
	{
		return pair.second;
	});
	return std::move(result);
}

std::vector<CubA4::world::ChunkPos> Dimension::getLoadedChunks()
{
	std::vector<CubA4::world::ChunkPos> result(loadedChunks_.size());
	std::transform(loadedChunks_.begin(), loadedChunks_.end(), result.begin(), [](auto pair) -> CubA4::world::ChunkPos
	{
		return pair.first;
	});
	return std::move(result);
}

std::vector<CubA4::world::ChunkPos> Dimension::getActiveChunks()
{
	std::vector<CubA4::world::ChunkPos> result(activeChunks_.size());
	std::transform(activeChunks_.begin(), activeChunks_.end(), result.begin(), [](auto pos) -> CubA4::world::ChunkPos
	{
		return pos;
	});
	return std::move(result);
}

void Dimension::onChunkLoaded(std::shared_ptr<Chunk> chunk)
{
	loadedChunks_.insert(std::make_pair(chunk->getChunkPos(), chunk));
}

void Dimension::onChunkActived(CubA4::world::ChunkPos position)
{
	activeChunks_.insert(position);
}

void Dimension::onChunkUnload(CubA4::world::ChunkPos position)
{
	if (auto it = loadedChunks_.find(position); it != loadedChunks_.end())
	{
		loadedChunks_.erase(it);
	}
}

void Dimension::onChunkDeactivated(CubA4::world::ChunkPos position)
{
	activeChunks_.erase(position);
}

std::shared_ptr<const IChunk> Dimension::findChunk(CubA4::world::ChunkPos pos) const
{
	auto it = loadedChunks_.find(pos);
	if (it == loadedChunks_.end())
		return {};
	return it->second;
}

std::shared_ptr<Chunk> Dimension::findChunk(CubA4::world::ChunkPos pos)
{
	auto it = loadedChunks_.find(pos);
	if (it == loadedChunks_.end())
		return {};
	return it->second;
}