#include "Chunk.hpp"
#include <object/IBlock.hpp>
#include <algorithm>
#include <execution>
#include <range/v3/view/map.hpp>
#include <range/v3/range/conversion.hpp>
using namespace CubA4::world;
using namespace CubA4::object;

Chunk::Chunk(const ChunkPos &chunkPos) :
	chunkPos_(chunkPos)
{
	
}

Chunk::~Chunk()
{
	
}

const ChunkPos &Chunk::getChunkPos() const
{
	return chunkPos_;
}

std::vector<std::shared_ptr<const IBlock>> Chunk::getUsedBlocks() const
{
	return usedBlocks | ranges::views::keys | ranges::to<std::vector>;
}

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers() const
{
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers;
	containers.resize(chunkBRanges_.size() + chunkBSets_.size() + chunkBMultis_.size());
	size_t idx = 0;
	for (auto range : chunkBRanges_)
	{
		containers[idx++] = range;
	}
	for (auto set : chunkBSets_)
	{
		containers[idx++] = set;
	}
	for (auto multi : chunkBMultis_)
	{
		containers[idx++] = multi;
	}
	return std::move(containers);
}

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock) const
{
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers;
	containers.resize(chunkBRanges_.size() + chunkBSets_.size() + chunkBMultis_.size());
	size_t idx = 0;
	for (auto range : chunkBRanges_)
	{
		if (range->getBlock() != usedBlock)
			continue;
		containers[idx++] = range;
	}
	for (auto set : chunkBSets_)
	{
		if (set->getBlock() != usedBlock)
			continue;
		containers[idx++] = set;
	}
	for (auto multi : chunkBMultis_)
	{
		if (multi->getBlock() != usedBlock)
			continue;
		containers[idx++] = multi;
	}
	const auto removeFrom = containers.begin() + idx;
	containers.erase(removeFrom, containers.end());
	return std::move(containers);
}

std::vector<CubA4::world::BlockAt> Chunk::getBlocksAt(world::BlockInChunkPos pos) const
{
	std::vector<BlockAt> blocks;
	auto checkContainer = [&blocks, pos](const auto &containers)
	{
		for (auto container : containers)
		{
			if (container->hasBlockAt(pos))
			{
				blocks.push_back(BlockAt {
					.block = container->getBlock(),
					.pos = pos,
					.layer = container->getLayer()
				});
			}
		}
	};
	checkContainer(chunkBRanges_);
	checkContainer(chunkBSets_);
	checkContainer(chunkBMultis_);
	std::sort(std::execution::par_unseq, blocks.begin(), blocks.end(), [](const auto &a, const auto &b) -> bool
	{
		return a.layer < b.layer;
	});
	return std::move(blocks);
}

CubA4::world::BlockAt Chunk::getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const
{
	auto checkContainer = [pos, layer](const auto &containers) -> BlockAt
	{
		for (auto container : containers)
		{
			if (container->getLayer() != layer)
				continue;
			if (container->hasBlockAt(pos))
			{
				return BlockAt {
					.block = container->getBlock(),
					.pos = pos,
					.layer = container->getLayer()
				};
			}
		}
		return {};
	};
	if (auto blockAt = checkContainer(chunkBRanges_); blockAt.block)
		return blockAt;
	if (auto blockAt = checkContainer(chunkBSets_); blockAt.block)
		return blockAt;
	if (auto blockAt = checkContainer(chunkBMultis_); blockAt.block)
		return blockAt;
	return {};
}

DataProvider &Chunk::getDataProvider()
{
	return dataProvider_;
}

const DataProvider &Chunk::getDataProvider() const
{
	return dataProvider_;
}

void Chunk::addRange(std::shared_ptr<ChunkBRange> container)
{
	chunkBRanges_.push_back(container);
	onContainerAdded(container);
}

void Chunk::onContainerAdded(std::shared_ptr<const IChunkBBaseContainer> container)
{
	const auto block = container->getBlock();
	auto it = usedBlocks.find(block);
	if (it == usedBlocks.end())
		usedBlocks.insert(std::make_pair(block, 1u));
	else
		it->second++;
}

void Chunk::onContainerRemoved(std::shared_ptr<const IChunkBBaseContainer> container)
{
	const auto block = container->getBlock();
	auto it = usedBlocks.find(block);
	if (it == usedBlocks.end() || !it->second)
	{
		// assert!
		return;
	}
	
	it->second--;
	if (!it->second)
		usedBlocks.erase(it);
}