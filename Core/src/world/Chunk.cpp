#include "Chunk.hpp"
#include <object/IBlock.hpp>
using namespace CubA4::world;
using namespace CubA4::mod::world;
using namespace CubA4::mod::object;

Chunk::Chunk(const CubA4::mod::world::ChunkPos &chunkPos) :
	chunkPos_(chunkPos), globalLock_(false)
{
	
}

Chunk::~Chunk()
{
	
}

std::vector<std::shared_ptr<const IBlock>> Chunk::getUsedBlocks() const
{
	Locker locker(globalLock_);
	auto copy = usedBlocks_;
	return std::move(copy);
}

std::vector<BlockInChunkPos> Chunk::getChunkPositions(const std::shared_ptr<const IBlock> usedBlock) const
{
	Locker locker(globalLock_);
	auto copy = usedBlockInfos_.find(usedBlock->getId())->second.chunkPositions;
	return std::move(copy);
}

const CubA4::mod::world::ChunkPos &Chunk::getChunkPos() const
{
	return chunkPos_;
}

void Chunk::placeBlocks(std::shared_ptr<const IBlock> block, std::vector<BlockInChunkPos> positions)
{
	Locker locker(globalLock_);
	auto it = usedBlockInfos_.find(block->getId());
	if (it == usedBlockInfos_.end())
	{
		usedBlocks_.push_back(block);
		usedBlockInfos_.insert(std::make_pair(block->getId(), UsedBlockInfo {block, positions}));
	}
	else
	{
		auto &chunkPositions = it->second.chunkPositions;
		chunkPositions.insert(chunkPositions.end(), positions.begin(), positions.end());
	}
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