#include "./ChunkRange.hpp"
#include <string.h>
#include <cmath>
using namespace CubA4::object;
using namespace CubA4::world;

ChunkRange::ChunkRange(std::shared_ptr<const IBlock> block,
	const std::array<BlockInChunkPos, BoundsSize> &bounds, CubA4::world::Layer layer) :
	block_(block), bounds_(bounds), layer_(layer)
{
}

ChunkRange::~ChunkRange()
{
	
}

std::shared_ptr<const IBlock> ChunkRange::getBlock() const
{
	return block_;
}

const ChunkRange::Bounds &ChunkRange::getBounds() const
{
	return bounds_;
}

ChunkRange::Bounds ChunkRange::getSideRect(BlockSide side) const
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
}

uint32_t ChunkRange::getBlockCount() const
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

CubA4::world::Layer ChunkRange::getLayer() const
{
	return layer_;
}

ChunkRange::Iterator ChunkRange::begin() const
{
	return Iterator(this, bounds_[0], 0);
}

ChunkRange::Iterator ChunkRange::end() const
{
	return Iterator(this, bounds_[1], getBlockCount());
}