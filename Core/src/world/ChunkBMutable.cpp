#include <world/ChunkBMutable.hpp>
using namespace CubA4::world;

ChunkBMutable::ChunkBMutable(size_t id, std::shared_ptr<const object::IBlock> block) :
    id_(id), block_(block)
{
	
}

ChunkBMutable::~ChunkBMutable()
{
	
}

size_t ChunkBMutable::getId() const
{
    return id_;
}

std::shared_ptr<const CubA4::object::IBlock> ChunkBMutable::getBlock() const
{
    return block_;
}

uint32_t ChunkBMutable::getBlockCount() const
{
    return static_cast<uint32_t>(blockMap_.size());
}

CubA4::world::Layer ChunkBMutable::getLayer() const
{
    return layer_;
}

bool ChunkBMutable::hasBlockAt(const world::BlockInChunkPos &pos) const
{
    return blockMap_.find(pos) != blockMap_.end();
}

uint32_t ChunkBMutable::getBlockIndex(const world::BlockInChunkPos &pos) const
{
    return static_cast<uint32_t>(std::distance(blockMap_.begin(), blockMap_.find(pos)));
}

CubA4::world::BlockInChunkPos ChunkBMutable::getBlockPosition(uint32_t index) const
{
    auto it = blockMap_.begin();
    std::advance(it, index);
    return it->first;
}

const BlockData &ChunkBMutable::getBlockData(const world::BlockInChunkPos &pos) const
{
    const auto id = blockMap_.find(pos)->second;
    return *dataMap_.find(id)->second.data;
}

void ChunkBMutable::addBlockAt(const world::BlockInChunkPos &pos, std::shared_ptr<BlockData> data)
{
    if (auto it = dataMap_.find(data->id); it != dataMap_.end())
    {
        it->second.usage++;
    }
    else
    {
        dataMap_.insert(std::make_pair(data->id, BlockDataInternal{data, 1}));
    }
    blockMap_.insert(std::make_pair(pos, data->id));
}

void ChunkBMutable::deleteBlockAt(const world::BlockInChunkPos &pos)
{
    auto it = blockMap_.find(pos);
    if (it == blockMap_.end())
        return;
    auto dataIt = dataMap_.find(it->second);
    if (dataIt != dataMap_.end())
    {
        dataIt->second.usage--;
        if (dataIt->second.usage <= 0)
            dataMap_.erase(dataIt);
    }
    
    blockMap_.erase(it);
}

ChunkBMutable::Iterator ChunkBMutable::begin() const
{
    return Iterator(std::make_unique<MutableIterator>(this, 0));
}

ChunkBMutable::Iterator ChunkBMutable::end() const
{
    return Iterator(std::make_unique<MutableIterator>(this, getBlockCount()));
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