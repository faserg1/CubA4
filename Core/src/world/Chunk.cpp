#include "Chunk.hpp"
#include <object/IBlock.hpp>
#include <algorithm>
#include <execution>
#include <range/v3/view/map.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/action/transform.hpp>
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
	auto tf = [](auto sContainer) -> std::shared_ptr<const IChunkBBaseContainer> { return sContainer; };
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers = containers_ | ranges::views::transform(tf) | ranges::to_vector;
	return std::move(containers);
}

std::vector<std::shared_ptr<IChunkBBaseContainer>> Chunk::getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock)
{
	std::vector<std::shared_ptr<IChunkBBaseContainer>> containers = containers_
		| ranges::views::remove_if([usedBlock](auto container){ return container->getBlock() != usedBlock; })
		| ranges::to_vector;
	return std::move(containers);
}

std::vector<std::shared_ptr<IChunkBBaseContainer>> Chunk::getChunkBContainers()
{
	return containers_;
}

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock) const
{
	auto tf = [](auto sContainer) -> std::shared_ptr<const IChunkBBaseContainer> { return sContainer; };
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers = containers_
		| ranges::views::remove_if([usedBlock](auto container){ return container->getBlock() != usedBlock; })
		| ranges::views::transform(tf)
		| ranges::to_vector;
	return std::move(containers);
}


bool Chunk::hasBlocksAt(world::BlockInChunkPos pos) const
{
	for (auto container : containers_)
	{
		if (container->hasBlockAt(pos))
			return true;
	}
	return false;
}

bool Chunk::hasBlocksAt(uint32_t index) const
{
	for (auto container : containers_)
	{
		if (container->hasBlockAt(index))
			return true;
	}
	return false;
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
	checkContainer(containers_);
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
	if (auto blockAt = checkContainer(containers_); blockAt.block)
		return blockAt;
	return {};
}

DataProvider &Chunk::getDataProvider()
{
	return dataProvider_;
}

const IDataProvider &Chunk::getDataProvider() const
{
	return dataProvider_;
}

void Chunk::addContainer(std::shared_ptr<IChunkBBaseContainer> container)
{
	containers_.push_back(container);
	onContainerAdded(container);
}

void Chunk::removeContainer(size_t idContainer)
{
	// todo
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