#include <world/ChunkBMulti.hpp>
using namespace CubA4::world;

ChunkBMulti::ChunkBMulti(size_t id, std::shared_ptr<const object::IBlock> block, CubA4::world::Layer layer, std::map<world::BlockInChunkPos, std::shared_ptr<BlockData>> data) :
    id_(id), block_(block), layer_(layer), data_(data)
{
	
}

ChunkBMulti::~ChunkBMulti()
{
	
}

size_t ChunkBMulti::getId() const
{
    return id_;
}

std::shared_ptr<const CubA4::object::IBlock> ChunkBMulti::getBlock() const
{
    return block_;
}

uint32_t ChunkBMulti::getBlockCount() const
{
    return static_cast<uint32_t>(data_.size());
}

CubA4::world::Layer ChunkBMulti::getLayer() const
{
    return layer_;
}

bool ChunkBMulti::hasBlockAt(const world::BlockInChunkPos &pos) const
{
    return data_.find(pos) != data_.end();
}

uint32_t ChunkBMulti::getBlockIndex(const world::BlockInChunkPos &pos) const
{
    return static_cast<uint32_t>(std::distance(data_.begin(), data_.find(pos)));
}

CubA4::world::BlockInChunkPos ChunkBMulti::getBlockPosition(uint32_t index) const
{
    auto it = data_.begin();
    std::advance(it, index);
    return it->first;
}

const BlockData &ChunkBMulti::getBlockData(const world::BlockInChunkPos &pos) const
{
    return *data_.find(pos)->second;
}

ChunkBMulti::Iterator ChunkBMulti::begin() const
{
    return Iterator(std::make_unique<MultiIterator>(this, 0));
}

ChunkBMulti::Iterator ChunkBMulti::end() const
{
    return Iterator(std::make_unique<MultiIterator>(this, getBlockCount()));
}

ChunkBMulti::MultiIterator::MultiIterator(const ChunkBMulti *multi, uint32_t index):
    multi_(multi), index_(index), pos_(multi->getBlockPosition(index))
{

}

std::unique_ptr<IChunkBIterator> ChunkBMulti::MultiIterator::copy() const
{
    auto rangeIt = std::make_unique<MultiIterator>(multi_, index_);
    rangeIt->pos_ = pos_;
    return std::move(rangeIt);
}

bool ChunkBMulti::MultiIterator::equal(const IChunkBIterator *other) const
{
    auto rangeIter = dynamic_cast<const MultiIterator*>(other);
    return rangeIter && rangeIter->multi_ == multi_ && rangeIter->index_ == index_;
}

void ChunkBMulti::MultiIterator::move(int32_t shift)
{
    index_ += shift;
    if (!multi_)
    {
        // assert
    }
    pos_ = multi_->getBlockPosition(index_);
}

const CubA4::world::BlockInChunkPos &ChunkBMulti::MultiIterator::get() const
{
    return pos_;
}