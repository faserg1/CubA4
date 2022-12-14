#include <world/ChunkBSet.hpp>
#include <execution>
#include <algorithm>
using namespace CubA4::world;

ChunkBSet::ChunkBSet(std::shared_ptr<const object::IBlock> block, std::vector<BlockInChunkPos> positions, std::shared_ptr<BlockData> data, Layer layer) :
    block_(block), positions_(std::move(positions)), data_(std::move(data)), layer_(layer)
{
	
}

ChunkBSet::~ChunkBSet()
{
	
}

std::shared_ptr<const CubA4::object::IBlock> ChunkBSet::getBlock() const
{
    return block_;
}

uint32_t ChunkBSet::getBlockCount() const
{
    return static_cast<uint32_t>(positions_.size());
}

bool ChunkBSet::hasBlockAt(const BlockInChunkPos &pos) const
{
    return std::any_of(std::execution::par_unseq, positions_.begin(), positions_.end(), [&pos](auto &setPos) -> bool
    {
        return setPos == pos;
    });
}

uint32_t ChunkBSet::getBlockIndex(const BlockInChunkPos &pos) const
{
    auto it = std::find(std::execution::par_unseq, positions_.begin(), positions_.end(), pos);
    if (it != positions_.end())
        return static_cast<uint32_t>(std::distance(positions_.begin(), it));
    return {};
}

BlockInChunkPos ChunkBSet::getBlockPosition(uint32_t index) const
{
    return positions_[index];
}

const BlockData &ChunkBSet::getBlockData(const BlockInChunkPos &pos) const
{
    return *data_;
}

Layer ChunkBSet::getLayer() const
{
    return layer_;
}

ChunkBSet::Iterator ChunkBSet::begin() const
{
    return Iterator(std::make_unique<SetIterator>(this, 0));
}

ChunkBSet::Iterator ChunkBSet::end() const
{
    return Iterator(std::make_unique<SetIterator>(this, getBlockCount()));
}

ChunkBSet::SetIterator::SetIterator(const ChunkBSet *set, uint32_t index):
    set_(set), index_(index), pos_(set->getBlockPosition(index))
{

}

std::unique_ptr<IChunkBIterator> ChunkBSet::SetIterator::copy() const
{
    auto rangeIt = std::make_unique<SetIterator>(set_, index_);
    rangeIt->pos_ = pos_;
    return std::move(rangeIt);
}

bool ChunkBSet::SetIterator::equal(const IChunkBIterator *other) const
{
    auto rangeIter = dynamic_cast<const SetIterator*>(other);
    return rangeIter && rangeIter->set_ == set_ && rangeIter->index_ == index_;
}

void ChunkBSet::SetIterator::move(int32_t shift)
{
    index_ += shift;
    if (!set_)
    {
        // assert
    }
    pos_ = set_->getBlockPosition(index_);
}

const CubA4::world::BlockInChunkPos &ChunkBSet::SetIterator::get() const
{
    return pos_;
}