#include <world/containers/ChunkBMutable.hpp>
#include <limits>
using namespace CubA4::world;

constexpr const auto BlockDataIDNone = std::numeric_limits<decltype(BlockData::id)>::max();

ChunkBMutable::ChunkBMutable(size_t id, CubA4::core::IIdentityiMap::IdType blockId, CubA4::world::Layer layer) :
    id_(id), blockId_(blockId), layer_(layer)
{
	blockMap_.fill(BlockDataIDNone);
}

ChunkBMutable::~ChunkBMutable()
{
	
}

size_t ChunkBMutable::getId() const
{
    return id_;
}

bool ChunkBMutable::isIndexGlobal() const
{
	return true;
}

CubA4::core::IIdentityiMap::IdType ChunkBMutable::getBlockId() const
{
    return blockId_;
}

uint32_t ChunkBMutable::getBlockCount() const
{
    return blockCount_;
}

CubA4::world::Layer ChunkBMutable::getLayer() const
{
    return layer_;
}

bool ChunkBMutable::hasBlockAt(const world::BlockInChunkPos &pos) const
{
    return blockMap_[getBlockIndex(pos)] != BlockDataIDNone;
}

bool ChunkBMutable::hasBlockAt(uint32_t index) const
{
	return blockMap_[index] != BlockDataIDNone;
}

uint32_t ChunkBMutable::getBlockIndex(const world::BlockInChunkPos &pos) const
{
    return static_cast<uint32_t>(indexByPos(pos));
}

uint32_t ChunkBMutable::getBlockLocalIndex(const world::BlockInChunkPos &pos) const
{
	const auto max = BlockDataIDNone;
	const auto giMax = indexByPos(pos);
	uint32_t li = 0;
	for (uint32_t gi = 0; gi < giMax; gi++)
	{
		if (blockMap_[gi] != max)
			li++;
	}
	return li;
}

CubA4::world::BlockInChunkPos ChunkBMutable::getBlockPosition(uint32_t index) const
{
    return posByIndex(index);
}

CubA4::world::BlockInChunkPos ChunkBMutable::getBlockPositionLocal(uint32_t localIndex) const
{
	uint32_t gi = 0;
	const auto max = BlockDataIDNone;
	for (uint32_t li = 0; li < localIndex; gi++)
	{
		if (blockMap_[gi] != max)
			li++;
	}
	return posByIndex(gi);
}

decltype(BlockData::id) ChunkBMutable::getBlockData(const world::BlockInChunkPos &pos) const
{
	return blockMap_[indexByPos(pos)];
}

decltype(BlockData::id) ChunkBMutable::getBlockData(uint32_t index) const
{
	return blockMap_[index];
}

void ChunkBMutable::setBlockAt(const world::BlockInChunkPos &pos, decltype(BlockData::id) dataId)
{
	setBlockAt(static_cast<uint32_t>(indexByPos(pos)), dataId);
}

void ChunkBMutable::setBlockAt(uint32_t index, decltype(BlockData::id) dataId)
{
	const auto max = BlockDataIDNone;
	if (blockMap_[index] == max && dataId != max)
		blockCount_++;
	else if (blockMap_[index] != max && dataId == max)
		blockCount_--;
	blockMap_[index] = dataId;
}

void ChunkBMutable::deleteBlockAt(const world::BlockInChunkPos &pos)
{
	deleteBlockAt(static_cast<uint32_t>(indexByPos(pos)));
}

void ChunkBMutable::deleteBlockAt(uint32_t index)
{
	setBlockAt(index, std::numeric_limits<decltype(BlockData::id)>::max());
}

ChunkBMutable::Iterator ChunkBMutable::begin() const
{
    return Iterator(std::make_unique<MutableIterator>(this, 0));
}

ChunkBMutable::Iterator ChunkBMutable::end() const
{
    return Iterator(std::make_unique<MutableIterator>(this, ChunkCube));
}

ChunkBMutable::MutableIterator::MutableIterator(const ChunkBMutable *cMutable, uint32_t index):
    mutable_(cMutable), index_(index), pos_(mutable_->getBlockPosition(index))
{

}

std::unique_ptr<IChunkBIterator> ChunkBMutable::MutableIterator::copy() const
{
    auto rangeIt = std::make_unique<MutableIterator>(mutable_, index_);
    rangeIt->pos_ = pos_;
    return std::move(rangeIt);
}

bool ChunkBMutable::MutableIterator::equal(const IChunkBIterator *other) const
{
    auto rangeIter = dynamic_cast<const MutableIterator*>(other);
    return rangeIter && rangeIter->mutable_ == mutable_ && rangeIter->index_ == index_;
}

void ChunkBMutable::MutableIterator::move(int32_t shift)
{
    index_ += shift;
    if (!mutable_)
    {
        // assert
    }
    pos_ = mutable_->getBlockPosition(index_);
}

const CubA4::world::BlockInChunkPos &ChunkBMutable::MutableIterator::get() const
{
    return pos_;
}