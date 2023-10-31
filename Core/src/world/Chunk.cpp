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

std::vector<CubA4::core::IIdentityiMap::IdType> Chunk::getUsedBlocks() const
{
	return usedBlocks_ | ranges::views::keys | ranges::to<std::vector>;
}

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers() const
{
	auto tf = [](auto sContainer) -> std::shared_ptr<const IChunkBBaseContainer> { return sContainer; };
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers = containers_ | ranges::views::transform(tf) | ranges::to_vector;
	return std::move(containers);
}

std::vector<std::shared_ptr<IChunkBBaseContainer>> Chunk::getChunkBContainers(CubA4::core::IIdentityiMap::IdType usedBlockId)
{
	std::vector<std::shared_ptr<IChunkBBaseContainer>> containers = containers_
		| ranges::views::remove_if([usedBlockId](auto container){ return container->getBlockId() != usedBlockId; })
		| ranges::to_vector;
	return std::move(containers);
}

std::vector<std::shared_ptr<IChunkBBaseContainer>> Chunk::getChunkBContainers()
{
	return containers_;
}

std::vector<std::shared_ptr<const IChunkBBaseContainer>> Chunk::getChunkBContainers(CubA4::core::IIdentityiMap::IdType usedBlockId) const
{
	auto tf = [](auto sContainer) -> std::shared_ptr<const IChunkBBaseContainer> { return sContainer; };
	std::vector<std::shared_ptr<const IChunkBBaseContainer>> containers = containers_
		| ranges::views::remove_if([usedBlockId](auto container){ return container->getBlockId() != usedBlockId; })
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
					.blockId = container->getBlockId(),
					.dataId = container->getBlockData(pos),
					.pos = pos,
					.layer = container->getLayer(),
					.containerId = container->getId()
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
					.blockId = container->getBlockId(),
					.dataId = container->getBlockData(pos),
					.pos = pos,
					.layer = container->getLayer(),
					.containerId = container->getId()
				};
			}
		}
		return {};
	};
	if (auto blockAt = checkContainer(containers_); blockAt.blockId)
		return blockAt;
	return {};
}

std::vector<CubA4::world::BlockAt> Chunk::getBlocksAt(uint32_t index) const
{
	std::vector<BlockAt> blocks;
	auto checkContainer = [&blocks, index](const auto &containers)
	{
		for (auto container : containers)
		{
			if (container->hasBlockAt(index))
			{
				blocks.push_back(BlockAt {
					.blockId = container->getBlockId(),
					.dataId = container->getBlockData(index),
					.pos = posByIndex(index),
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

CubA4::world::BlockAt Chunk::getBlockAt(uint32_t index, world::Layer layer) const
{
	auto checkContainer = [index, layer](const auto &containers) -> BlockAt
	{
		for (auto container : containers)
		{
			if (container->getLayer() != layer)
				continue;
			if (container->hasBlockAt(index))
			{
				return BlockAt {
					.blockId = container->getBlockId(),
					.dataId = container->getBlockData(index),
					.pos = posByIndex(index),
					.layer = container->getLayer()
				};
			}
		}
		return {};
	};
	if (auto blockAt = checkContainer(containers_); blockAt.blockId)
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
	auto pred = [idContainer](auto container) -> bool { return container->getId() == idContainer; };
	if (auto it = std::find_if(containers_.begin(), containers_.end(), pred); it != containers_.end())
	{
		onContainerRemoved(*it);
		containers_.erase(it);
	}
		
}

std::shared_ptr<IChunkBBaseContainer> Chunk::getContainer(size_t idContainer)
{
	auto pred = [idContainer](auto container) -> bool { return container->getId() == idContainer; };
	auto it = std::find_if(containers_.begin(), containers_.end(), pred);
	if (it != containers_.end())
		return *it;
	return nullptr;
}

size_t Chunk::allocateIdContainer()
{
	return genId_++;
}

void Chunk::erase()
{
	auto tf = [](auto sContainer) -> size_t { return sContainer->getId(); };
	std::vector<size_t> ids = containers_
		| ranges::views::transform(tf)
		| ranges::to_vector;
	for (auto id : ids)
	{
		removeContainer(id);
	}
}

void Chunk::onContainerAdded(std::shared_ptr<const IChunkBBaseContainer> container)
{
	const auto blockId = container->getBlockId();
	auto it = usedBlocks_.find(blockId);
	if (it == usedBlocks_.end())
		usedBlocks_.insert(std::make_pair(blockId, 1u));
	else
		it->second++;
}

void Chunk::onContainerRemoved(std::shared_ptr<const IChunkBBaseContainer> container)
{
	const auto blockId = container->getBlockId();
	auto it = usedBlocks_.find(blockId);
	if (it == usedBlocks_.end() || !it->second)
	{
		// assert!
		return;
	}
	
	it->second--;
	if (!it->second)
		usedBlocks_.erase(it);
}