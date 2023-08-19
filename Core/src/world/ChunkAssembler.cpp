#include <world/ChunkAssembler.hpp>
#include <execution>
#include <algorithm>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <limits>
using namespace CubA4::world;

ChunkAssembler::ChunkAssembler(CubA4::core::IEnvironment &env) :
	env_(env)
{
	
}

ChunkAssembler::~ChunkAssembler()
{
	
}

void ChunkAssembler::applyChanges(std::shared_ptr<Chunk> chunk, const ChunkBModification &mod)
{
	auto &dataProvider = chunk->getDataProvider();
	for (const auto &addBlockChange : mod.add)
	{
		auto containers = chunk->getChunkBContainers(addBlockChange.blockId);
		auto &blockDataStorage = dataProvider.getBlockDataStorage(addBlockChange.blockId);

		std::shared_ptr<ChunkBMutable> choosedContainer;
		if (containers.empty())
		{
			choosedContainer = std::make_shared<ChunkBMutable>(chunk->allocateIdContainer(), addBlockChange.blockId, 0);
			chunk->addContainer(choosedContainer);
		}
		for (auto container : containers)
		{
			if (container->hasBlockAt(addBlockChange.pos))
				continue;
			choosedContainer = std::dynamic_pointer_cast<ChunkBMutable>(container);
			break;
		}
		if (!choosedContainer)
		{
			choosedContainer = std::make_shared<ChunkBMutable>(chunk->allocateIdContainer(), addBlockChange.blockId, 0);
			chunk->addContainer(choosedContainer);
		}

		auto data = blockDataStorage.getOrAdd(addBlockChange.data);
		choosedContainer->setBlockAt(addBlockChange.pos, data->id);
	}
	// TODO: implement remove, mod
}

std::shared_ptr<Chunk> ChunkAssembler::createChunk(const ChunkBGeneration &gen)
{
	auto chunk = std::make_shared<Chunk>(gen.pos);
	auto &dataProvider = chunk->getDataProvider();
	Layer layerPos = 0;
	for (const auto &layer : gen.layers)
	{
		std::map<CubA4::core::IIdentityiMap::IdType, std::shared_ptr<ChunkBMutable>> containerMap;
		for (const auto &addInfo : layer.add)
		{
			auto &info = addInfo.info;
			if (info.blockId == std::numeric_limits<CubA4::core::IIdentityiMap::IdType>::max())
				continue;
			auto &blockDataStorage = dataProvider.getBlockDataStorage(info.blockId);
			auto data = blockDataStorage.getOrAdd(*info.data);
			std::shared_ptr<ChunkBMutable> choosedContainer;
			if (auto it = containerMap.find(info.blockId); it != containerMap.end())
				choosedContainer = it->second;
			else
			{
				// Pass the right id
				choosedContainer = std::make_shared<ChunkBMutable>(0, info.blockId, layerPos);
				chunk->addContainer(choosedContainer);
			}
			for (auto pos : addInfo.positions)
				choosedContainer->setBlockAt(pos, data->id);
		}
		for (const auto &fillInfo : layer.fill)
		{
			auto &info = fillInfo.info;
			// TODO: Copy paste refactor
			if (info.blockId == std::numeric_limits<CubA4::core::IIdentityiMap::IdType>::max())
				continue;
			auto &blockDataStorage = dataProvider.getBlockDataStorage(info.blockId);
			auto data = blockDataStorage.getOrAdd(*info.data);
			std::shared_ptr<ChunkBMutable> choosedContainer;
			if (auto it = containerMap.find(info.blockId); it != containerMap.end())
				choosedContainer = it->second;
			else
			{
				// Pass the right id
				choosedContainer = std::make_shared<ChunkBMutable>(0, info.blockId, layerPos);
				chunk->addContainer(choosedContainer);
			}
			// TODO: impl
		}
		++layerPos;
	}
	return chunk;
}

uint8_t ChunkAssembler::countAdjancentBlocks(CubA4::world::BlockInChunkPos start, std::function<bool(CubA4::world::BlockInChunkPos)> checker)
{
	uint8_t count = 0;
	for (const auto adjancentPos : AdjancentPositions)
	{
		const auto neighborPos = start + adjancentPos;
		if (neighborPos.x < 0 || neighborPos.x >= ChunkSize
			|| neighborPos.y < 0 || neighborPos.y >= ChunkSize
			|| neighborPos.z < 0 || neighborPos.z >= ChunkSize)
		{
			// Skip if neighborPos is out of bounds
			continue;
		}
		if (checker(neighborPos))
			count++;
	}
	return count;
}

uint8_t ChunkAssembler::countAdjancentWithCornersBlocks(CubA4::world::BlockInChunkPos start, std::function<bool(CubA4::world::BlockInChunkPos)> checker)
{
	uint8_t count = 0;
	for (const auto adjancentPos : AdjancentWithCornersPositions)
	{
		const auto neighborPos = start + adjancentPos;
		if (neighborPos.x < 0 || neighborPos.x >= ChunkSize
			|| neighborPos.y < 0 || neighborPos.y >= ChunkSize
			|| neighborPos.z < 0 || neighborPos.z >= ChunkSize)
		{
			// Skip if neighborPos is out of bounds
			continue;
		}
		if (checker(neighborPos))
			count++;
	}
	return count;
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