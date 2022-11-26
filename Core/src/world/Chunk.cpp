#include "Chunk.hpp"
#include "ChunkRange.hpp"
#include <object/IBlock.hpp>
#include <algorithm>
#include <execution>
using namespace CubA4::world;
using namespace CubA4::object;

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

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers() const
{
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers;
	containers.resize(chunkBRanges_.size() + chunkBSets_.size() + chunkBMultis_.size());
	size_t idx = 0;
	for (auto range : chunkBRanges_)
	{
		containers[idx++] = range;
	}
	for (auto set : chunkBSets_)
	{
		containers[idx++] = set;
	}
	for (auto multi : chunkBMultis_)
	{
		containers[idx++] = multi;
	}
	return std::move(containers);
}

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock) const
{
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers;
	containers.resize(chunkBRanges_.size() + chunkBSets_.size() + chunkBMultis_.size());
	size_t idx = 0;
	for (auto range : chunkBRanges_)
	{
		if (range->getBlock() != usedBlock)
			continue;
		containers[idx++] = range;
	}
	for (auto set : chunkBSets_)
	{
		if (set->getBlock() != usedBlock)
			continue;
		containers[idx++] = set;
	}
	for (auto multi : chunkBMultis_)
	{
		if (multi->getBlock() != usedBlock)
			continue;
		containers[idx++] = multi;
	}
	const auto removeFrom = containers.begin() + idx;
	containers.erase(removeFrom, containers.end());
	return std::move(containers);
}

std::vector<std::shared_ptr<const IChunkRange>> Chunk::getChunkRanges() const
{
	std::vector<std::shared_ptr<const IChunkRange>> rangesCopy;
	{
		Locker locker(globalLock_);
		rangesCopy.resize(chunkRanges_.size());
		std::copy(chunkRanges_.begin(), chunkRanges_.end(), rangesCopy.begin());
	}
	return std::move(rangesCopy);
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

std::vector<CubA4::world::BlockAt> Chunk::getBlocksAt(world::BlockInChunkPos pos) const
{
	std::vector<BlockAt> blocks;
	decltype(chunkRanges_) rangesCopy;
	{
		Locker locker(globalLock_);
		rangesCopy = chunkRanges_;
	}
	for (auto range : rangesCopy)
	{
		const auto &bounds = range->getBounds();
		if (isInBounds(bounds[0], bounds[1], pos))
			blocks.push_back(BlockAt {
				.block = range->getBlock(),
				.pos = pos,
				.layer = range->getLayer()
			});
	}
	return std::move(blocks);
}

CubA4::world::BlockAt Chunk::getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const
{
	std::vector<BlockAt> blocks;
	decltype(chunkRanges_) rangesCopy;
	{
		Locker locker(globalLock_);
		rangesCopy = chunkRanges_;
	}
	for (auto range : rangesCopy)
	{
		if (range->getLayer() != layer)
			continue;
		const auto &bounds = range->getBounds();
		if (isInBounds(bounds[0], bounds[1], pos))
		{
			return BlockAt {
				.block = range->getBlock(),
				.pos = pos,
				.layer = range->getLayer()
			};
		}
			
	}
	return {};
}

void Chunk::addBlock(std::shared_ptr<const object::IBlock>, world::BlockInChunkPos at)
{

}

void Chunk::fillWithBlock(std::shared_ptr<const object::IBlock>, world::BlockInChunkPos start, world::BlockInChunkPos end)
{

}


void Chunk::addChunkRange(std::shared_ptr<ChunkRange> chunkRange)
{
	Locker locker(globalLock_);
	chunkRanges_.push_back(chunkRange);
}

//////////////////////////////////////////////////////////////////////////

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