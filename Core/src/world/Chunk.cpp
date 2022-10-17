#include "Chunk.hpp"
#include "ChunkRange.hpp"
#include <object/IBlock.hpp>
#include <algorithm>
using namespace CubA4::world;
using namespace CubA4::core::world;
using namespace CubA4::mod::world;
using namespace CubA4::mod::object;

Chunk::Chunk(const ChunkPos &chunkPos) :
	chunkPos_(chunkPos), globalLock_(false)
{
	
}

Chunk::~Chunk()
{
	
}

const ChunkPos &Chunk::getChunkPos() const
{
	return chunkPos_;
}

std::vector<std::shared_ptr<const IBlock>> Chunk::getUsedBlocks() const
{
	decltype(chunkRanges_) rangesCopy;
	{
		Locker locker(globalLock_);
		rangesCopy = chunkRanges_;
	}
	std::vector<std::shared_ptr<const IBlock>> usedBlocks;
	for (std::shared_ptr<ChunkRange> range : rangesCopy)
	{
		const auto finded = std::find_if(usedBlocks.begin(), usedBlocks.end(), [range](std::shared_ptr<const IBlock> ptr) -> bool
		{
			return ptr == range->getBlock();
		});
		if (finded != usedBlocks.end())
			continue;
		usedBlocks.push_back(range->getBlock());
	}
	return std::move(usedBlocks);
}

std::vector<std::shared_ptr<const IChunkRange>> Chunk::getChunkRanges(const std::shared_ptr<const IBlock> usedBlock) const
{
	decltype(chunkRanges_) rangesCopy;
	{
		Locker locker(globalLock_);
		rangesCopy = chunkRanges_;
	}
	std::vector<std::shared_ptr<const IChunkRange>> rangesUsed;
	for (std::shared_ptr<ChunkRange> range : rangesCopy)
	{
		if (range->getBlock() != usedBlock)
			continue;
		rangesUsed.push_back(range);
	}
	return std::move(rangesUsed);
}

void Chunk::addChunkRange(std::shared_ptr<ChunkRange> chunkRange)
{
	Locker locker(globalLock_);
	chunkRanges_.push_back(chunkRange);
}

Chunk::Locker::Locker(std::atomic_bool &lock) :
	lock_(lock)
{
	while (lock_);
	lock_ = true;
}

Chunk::Locker::~Locker()
{
	lock_ = false;
}