#include <world/ChunkAssembler.hpp>
#include <execution>
#include <algorithm>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <limits>
using namespace CubA4::world;

ReassembledChunkContainers &ReassembledChunkContainers::operator+=(const ReassembledChunkContainers &other)
{
	addedMultis.insert_range(addedMultis.end(), other.addedMultis);
	addedRanges.insert_range(addedRanges.end(), other.addedRanges);
	addedSets.insert_range(addedSets.end(), other.addedSets);
	removed.insert_range(removed.end(), other.removed);
	return *this;
}

ChunkAssembler::ChunkAssembler(CubA4::system::IEnvironment &env) :
	env_(env)
{
	
}

ChunkAssembler::~ChunkAssembler()
{
	
}

ReassembledChunkContainers ChunkAssembler::reassemble(std::shared_ptr<Chunk> chunk, const ChunkBModification &modification)
{
	ReassembledChunkContainers rcc {};
	auto usedBlocks = chunk->getUsedBlocks();
	std::vector<ReassembledChunkContainers> rccByBlocks(usedBlocks.size());
	std::transform(usedBlocks.begin(), usedBlocks.end(), rccByBlocks.begin(), [this, chunk, &modification](std::shared_ptr<const CubA4::object::IBlock> block)
	{
		ChunkBModification mods;
		mods.add = modification.add | ranges::views::filter([block](auto mod) -> bool {return mod.block == block;}) | ranges::to<std::vector>;
		mods.mod = modification.mod;
		mods.remove = modification.remove;
		return reassembleByBlock(chunk, block, mods);
	});
	rcc = std::accumulate(rccByBlocks.begin(), rccByBlocks.end(), ReassembledChunkContainers {}, [](const ReassembledChunkContainers &a, const ReassembledChunkContainers &b) -> ReassembledChunkContainers
	{
		ReassembledChunkContainers total;
		total += a;
		total += b;
		return std::move(total);
	});
    return std::move(rcc);
}

ReassembledChunkContainers ChunkAssembler::reassembleByBlock(std::shared_ptr<Chunk> chunk, std::shared_ptr<const CubA4::object::IBlock> block, const ChunkBModification &modification)
{
	ReassembledChunkContainers rcc {};
	const auto id = env_.getId(block);
	auto &storage = chunk->getDataProvider().getBlockDataStorage(id);
	for (const auto &addMod : modification.add)
	{
		storage.getOrAdd(addMod.data);
	}
	std::vector<ReassembledChunkContainers> rccByBlockDatas(storage.getStorage().size());
	if (block->isMultilayered())
	{
		std::transform(storage.getStorage().begin(), storage.getStorage().end(), rccByBlockDatas.begin(), [this, chunk, block, &modification](std::shared_ptr<const BlockData> blockData)
		{
			return reassembleByBlockData(chunk, block, *blockData, modification);
		});
	}
	else
	{
		// TODO: [OOKAMI] Transform mutable
	}
	
	rcc = std::accumulate(rccByBlockDatas.begin(), rccByBlockDatas.end(), ReassembledChunkContainers {}, [](const ReassembledChunkContainers &a, const ReassembledChunkContainers &b) -> ReassembledChunkContainers
	{
		ReassembledChunkContainers total;
		total += a;
		total += b;
		return std::move(total);
	});
	return std::move(rcc);
}

ReassembledChunkContainers ChunkAssembler::reassembleByBlockData(std::shared_ptr<Chunk> chunk, std::shared_ptr<const CubA4::object::IBlock> block, BlockData data, const ChunkBModification &modification)
{
	ReassembledChunkContainers rcc {};
	struct BlockInfo
	{
		Layer layer = std::numeric_limits<Layer>::max();
		size_t containerId = std::numeric_limits<size_t>::max();
		size_t tempContainerId = std::numeric_limits<size_t>::max();
		ChunkBContainerType next = ChunkBContainerType::None;
	};
	
	using BlockInfoCollection = std::vector<BlockInfo>;
	std::array<BlockInfoCollection, ChunkCube> cube;
	for (auto container : chunk->getChunkBContainers(block))
	{
		for (auto blockPos : *container)
		{
			const auto index = indexByPos(blockPos);
			auto &blockInfoCollection = cube[index];
			blockInfoCollection.push_back(BlockInfo{container->getLayer(), container->getId()});
		}
	}
	// Remove blocks
	for (const auto &removeInfo : modification.remove)
	{
		const auto index = indexByPos(removeInfo.pos);
		auto &blockInfoCollection = cube[index];
		auto blockInfoIt = std::remove_if(blockInfoCollection.begin(), blockInfoCollection.end(), [layer = removeInfo.layer](const auto &bi)
		{
			return bi.layer == layer;
		});
		if (blockInfoIt == blockInfoCollection.end())
			continue;
		blockInfoCollection.erase(blockInfoIt);
	}

	// Helper for adding

	auto countAdjancentBlocks = [&cube](BlockInChunkPos pos, Layer layer) -> uint8_t {
		uint8_t count = 0;
		for (const auto adjancentPos : AdjancentPositions)
		{
			const auto neighborPos = pos + adjancentPos;
			if (neighborPos.x < 0 || neighborPos.x >= ChunkSize
				|| neighborPos.y < 0 || neighborPos.y >= ChunkSize
				|| neighborPos.z < 0 || neighborPos.z >= ChunkSize)
			{
				// Skip if neighborPos is out of bounds
				continue;
			}
			const auto adjancentIndex = indexByPos(neighborPos);
			const auto &blockInfoCollection = cube[adjancentIndex];
			for (const auto &blockInfo : blockInfoCollection)
			{
				if (blockInfo.layer == layer)
				{
					count++;
					break;
				}
			}
		}
		return count;
	};

	// Add blocks. Should try to insert in layer with more neighbors as possible
	for (const auto &addInfo : modification.add)
	{
		const auto index = indexByPos(addInfo.pos);
		auto &blockInfoCollection = cube[index];

		// Find the layer with the most neighbors
		Layer targetLayer = 0;
		int maxNeighbors = 0;
		for (const auto &blockInfo : blockInfoCollection)
		{
			if (blockInfo.layer > targetLayer)
			{
				const auto neighbors = countAdjancentBlocks(addInfo.pos, blockInfo.layer);
				if (neighbors > maxNeighbors)
				{
					targetLayer = blockInfo.layer;
					maxNeighbors = neighbors;
				}
			}
		}

		if (!maxNeighbors)
		{
			const auto blocks = chunk->getBlocksAt(addInfo.pos);
			
			Layer requestedLayer = 0;
			for (const auto &block : blocks)
			{
				if (block.layer == requestedLayer)
				{
					requestedLayer++;
				}
			}
		}

		blockInfoCollection.push_back(BlockInfo{targetLayer, std::numeric_limits<size_t>::max()});
	}

	// Find most occupied place. Start making range from center
	// Anything else would be range

	// ...
	
	return std::move(rcc);
}

std::shared_ptr<ChunkBRange> ChunkAssembler::buildRange(
	size_t id,
    std::shared_ptr<const CubA4::object::IBlock> block,
    const CubA4::world::BlockInChunkPos &start,
    const CubA4::world::BlockInChunkPos &end,
    BlockData data,
    CubA4::world::Layer layer)
{
    return std::make_shared<ChunkBRange>(id, block, minMaxBounds({start, end}), std::make_shared<BlockData>(data), layer);
}


std::array<BlockInChunkPos, MinMaxBoundsSize> ChunkAssembler::minMaxBounds(const std::vector<BlockInChunkPos> &positions)
{
	static_assert(MinMaxBoundsSize == 2, "Количество точек для минимальной/максимальной границы должно равнятся двум.");
	std::array<BlockInChunkPos, MinMaxBoundsSize> bounds;
	bounds[0] = minBound(positions);
	bounds[1] = maxBound(positions);
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