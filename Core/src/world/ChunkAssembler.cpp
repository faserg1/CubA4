#include <world/ChunkAssembler.hpp>
#include <execution>
#include <algorithm>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
using namespace CubA4::world;

ChunkAssembler::ChunkAssembler()
{
	
}

ChunkAssembler::~ChunkAssembler()
{
	
}

ReassembledChunkContainers ChunkAssembler::reassemble(std::shared_ptr<Chunk> chunk, const ChunkBModification &modification)
{
	ReassembledChunkContainers rcc {};
	auto usedBlocks = chunk->getUsedBlocks();
	std::vector<ReassembledChunkContainers> rccByBlocks;
	std::transform(usedBlocks.begin(), usedBlocks.end(), std::back_inserter(rccByBlocks), [this, chunk, &modification](std::shared_ptr<const CubA4::object::IBlock> block)
	{
		ChunkBModification mods;
		mods.add = modification.add | ranges::views::filter([block](auto mod) -> bool {return mod.block == block;}) | ranges::to<std::vector>;
		mods.remove = modification.remove;
		return reassembleByBlock(chunk, block, mods);
	});
	rcc = std::accumulate(rccByBlocks.begin(), rccByBlocks.end(), ReassembledChunkContainers {}, [](const ReassembledChunkContainers &a, const ReassembledChunkContainers &b) -> ReassembledChunkContainers
	{
		ReassembledChunkContainers total;
		total.addedMultis.insert_range(total.addedMultis.end(), a.addedMultis);
		total.addedMultis.insert_range(total.addedMultis.end(), b.addedMultis);

		total.addedRanges.insert_range(total.addedRanges.end(), a.addedRanges);
		total.addedRanges.insert_range(total.addedRanges.end(), b.addedRanges);
		
		total.addedSets.insert_range(total.addedSets.end(), a.addedSets);
		total.addedSets.insert_range(total.addedSets.end(), b.addedSets);

		total.removed.insert_range(total.removed.end(), a.removed);
		total.removed.insert_range(total.removed.end(), b.removed);
		
		return std::move(total);
	});
    return std::move(rcc);
}

ReassembledChunkContainers ChunkAssembler::reassembleByBlock(std::shared_ptr<Chunk> chunk, std::shared_ptr<const CubA4::object::IBlock> block, const ChunkBModification &modification)
{
	ReassembledChunkContainers rcc {};
	struct BlockInfo
	{
		uint32_t beginOfNextX;
		uint32_t beginOfNextY;
		uint32_t beginOfNextZ;
		BlockInfo *beginX = nullptr;
		BlockInfo *beginY = nullptr;
		BlockInfo *beginZ = nullptr;
		std::vector<std::shared_ptr<const IChunkBBaseContainer>> parentContainers;
	};
	std::array<BlockInfo, ChunkCube> cube;
	for (auto container : chunk->getChunkBContainers())
	{
		for (auto blockPos : *container)
		{
			const auto index = indexByPos(blockPos);
			const auto &blockInfo = cube[index];
		}
	}
	return std::move(rcc);
}

std::shared_ptr<ChunkBRange> ChunkAssembler::buildRange(
    std::shared_ptr<const CubA4::object::IBlock> block,
    const CubA4::world::BlockInChunkPos &start,
    const CubA4::world::BlockInChunkPos &end,
    BlockData data,
    CubA4::world::Layer layer)
{
    return std::make_shared<ChunkBRange>(block, minMaxBounds({start, end}), std::make_shared<BlockData>(data), layer);
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