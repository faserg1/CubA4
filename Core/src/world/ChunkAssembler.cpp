#include <world/ChunkAssembler.hpp>
#include <algorithm>
using namespace CubA4::world;

ChunkAssembler::ChunkAssembler()
{
	
}

ChunkAssembler::~ChunkAssembler()
{
	
}

ReassmebledChunkContainers ChunkAssembler::reassmeble(std::shared_ptr<Chunk> chunk, const ChunkBModification &modification)
{
    return {};
}

std::shared_ptr<ChunkBRange> ChunkAssembler::buildRange(
    std::shared_ptr<const CubA4::object::IBlock> block,
    const CubA4::world::BlockInChunkPos &start,
    const CubA4::world::BlockInChunkPos &end,
    BlockData data,
    CubA4::world::Layer layer)
{
    return std::make_shared<ChunkBRange>(block, minMaxBounds({start, end}), data, layer);
}


std::array<BlockInChunkPos, MinMaxBoundsSize> ChunkAssembler::minMaxBounds(const std::vector<BlockInChunkPos> &positions)
{
	static_assert(MinMaxBoundsSize == 2, "Количество точек для минимальной/максимальной границы должно равнятся двум.");
	std::array<BlockInChunkPos, MinMaxBoundsSize> bounds;
	bounds[MinIndex] = minBound(positions);
	bounds[MaxIndex] = maxBound(positions);
	return std::move(bounds);
}

BlockInChunkPos ChunkAssembler::minBound(const std::vector<BlockInChunkPos> &positions)
{
	BlockInChunkPos bound;
	auto find_min = [&positions, &bound](decltype(BlockInChunkPos::x) BlockInChunkPos::*coord)
	{
		bound.*coord = (*std::min_element(positions.begin(), positions.end(), [&coord](const auto &left, const auto &right) {return left.*coord < right.*coord; })).*coord;
	};
	find_min(&BlockInChunkPos::x);
	find_min(&BlockInChunkPos::y);
	find_min(&BlockInChunkPos::z);
	return bound;
}

BlockInChunkPos ChunkAssembler::maxBound(const std::vector<BlockInChunkPos> &positions)
{
	BlockInChunkPos bound;
	auto find_max = [&positions, &bound](decltype(BlockInChunkPos::x) BlockInChunkPos::*coord)
	{
		bound.*coord = (*std::max_element(positions.begin(), positions.end(), [&coord](const auto &left, const auto &right) {return left.*coord < right.*coord; })).*coord;
	};
	find_max(&BlockInChunkPos::x);
	find_max(&BlockInChunkPos::y);
	find_max(&BlockInChunkPos::z);
	return bound;
}

std::array<BlockInChunkPos, 8> ChunkAssembler::points(const BlockInChunkPos &min, const BlockInChunkPos &max)
{
	std::array<BlockInChunkPos, 8> coords;
	float zCounter = 0;
	for (uint8_t i = 0; i < 8; i++, zCounter += 0.5)
	{
		coords[i].x = (i < 4 ? min.x : max.x);
		coords[i].y = (i % 2 ? min.y : max.y);
		coords[i].z = (static_cast<uint8_t>(zCounter) % 2 ? min.z : max.z);
	}
	return std::move(coords);
}