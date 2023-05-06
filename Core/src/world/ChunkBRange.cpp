#include <world/ChunkBRange.hpp>
using namespace CubA4::world;

ChunkBRange::ChunkBRange(size_t id, std::shared_ptr<const object::IBlock> block,
	const std::array<BlockInChunkPos, BoundsSize> &bounds, std::shared_ptr<BlockData> data, Layer layer) :
        id_(id), block_(block), bounds_(bounds), data_(data), layer_(layer)
{
	
}

ChunkBRange::~ChunkBRange()
{
	
}

size_t ChunkBRange::getId() const
{
    return id_;
}

std::shared_ptr<const CubA4::object::IBlock> ChunkBRange::getBlock() const
{
	return block_;
}

const ChunkBRange::Bounds &ChunkBRange::getBounds() const
{
	return bounds_;
}

ChunkBRange::Bounds ChunkBRange::getSideRect(BlockSide side) const
{
	switch (side)
	{
	case BlockSide::Top:
		return {BlockInChunkPos{bounds_[0].x, bounds_[1].y, bounds_[1].z}, bounds_[1]};
	case BlockSide::Bottom:
		return {bounds_[0], BlockInChunkPos{bounds_[1].x, bounds_[0].y, bounds_[1].z}};
	case BlockSide::Left:
		return {bounds_[0], BlockInChunkPos{bounds_[0].x, bounds_[1].y, bounds_[1].z}};
	case BlockSide::Right:
		return {BlockInChunkPos{bounds_[1].x, bounds_[0].y, bounds_[0].z}, bounds_[1]};
	case BlockSide::Front:
		return {bounds_[0], BlockInChunkPos{bounds_[1].x, bounds_[1].y, bounds_[0].z}};
	case BlockSide::Back:
		return {BlockInChunkPos{bounds_[0].x, bounds_[0].y, bounds_[1].z}, bounds_[1]};
	}
	// exception
	return {};
}

uint32_t ChunkBRange::getBlockCount() const
{
	static_assert(BoundsSize == 2, "Для данной функции BoundsSize должен быть равен 2");
	auto diff = [](auto a, auto b)
	{
		if (a > b)
			return a - b + 1;
		return b - a + 1;
	};
	return
		diff(bounds_[0].x, bounds_[1].x) *
		diff(bounds_[0].y, bounds_[1].y) * 
		diff(bounds_[0].z, bounds_[1].z);
}

bool ChunkBRange::hasBlockAt(const world::BlockInChunkPos &pos) const
{
	return isInBounds(bounds_[0], bounds_[1], pos);
}

// TODO: Move index details to constexpr in Position.hpp

uint32_t ChunkBRange::getBlockIndex(const world::BlockInChunkPos &pos) const
{
	const auto xSize = bounds_[1].x - bounds_[0].x + 1;
	const auto ySize = bounds_[1].y - bounds_[0].y + 1;
	return ((pos.z - bounds_[0].z) * ySize * xSize) + ((pos.y - bounds_[0].y) * xSize) + (pos.x - bounds_[0].x);
}

CubA4::world::BlockInChunkPos ChunkBRange::getBlockPosition(uint32_t index) const
{
	using xType = decltype(CubA4::world::BlockInChunkPos::x);
	using yType = decltype(CubA4::world::BlockInChunkPos::y);
	using zType = decltype(CubA4::world::BlockInChunkPos::z);
    const auto xSize = bounds_[1].x - bounds_[0].x + 1;
	const auto ySize = bounds_[1].y - bounds_[0].y + 1;
    xType x = index % xSize;
    index -= x;
    yType y = (index % (ySize * xSize)) / xSize;
    index -= (y * xSize);
    zType z = index / (xSize * ySize);
    return {static_cast<xType>(bounds_[0].x + x), static_cast<yType>(bounds_[0].y + y), static_cast<zType>(bounds_[0].z + z)};
}

const BlockData &ChunkBRange::getBlockData(const world::BlockInChunkPos &pos) const
{
    return *data_;
}

CubA4::world::Layer ChunkBRange::getLayer() const
{
	return layer_;
}

ChunkBRange::Iterator ChunkBRange::begin() const
{
	return Iterator(std::make_unique<RangeIterator>(this, 0));
}

ChunkBRange::Iterator ChunkBRange::end() const
{
	return Iterator(std::make_unique<RangeIterator>(this, getBlockCount()));
}

ChunkBRange::RangeIterator::RangeIterator(const ChunkBRange *range, uint32_t index):
    range_(range), index_(index), pos_(range->getBlockPosition(index))
{

}

std::unique_ptr<IChunkBIterator> ChunkBRange::RangeIterator::copy() const
{
    auto rangeIt = std::make_unique<RangeIterator>(range_, index_);
    rangeIt->pos_ = pos_;
    return std::move(rangeIt);
}

bool ChunkBRange::RangeIterator::equal(const IChunkBIterator *other) const
{
    auto rangeIter = dynamic_cast<const RangeIterator*>(other);
    return rangeIter && rangeIter->range_ == range_ && rangeIter->index_ == index_;
}

void ChunkBRange::RangeIterator::move(int32_t shift)
{
    index_ += shift;
    if (!range_)
    {
        // assert
    }
    pos_ = range_->getBlockPosition(index_);
}

const CubA4::world::BlockInChunkPos &ChunkBRange::RangeIterator::get() const
{
    return pos_;
}