#pragma once

#include <world/IChunk.hpp>
#include <world/data/DataProvider.hpp>
#include <memory>
#include <vector>
#include <map>
#include <atomic>

namespace CubA4::world
{
	class Chunk :
		public virtual CubA4::world::IChunk
	{
	public:
		Chunk(const CubA4::world::ChunkPos &chunkPos);
		~Chunk();
		const CubA4::world::ChunkPos &getChunkPos() const override;
		std::vector<CubA4::system::IIdentityiMap::IdType> getUsedBlocks() const override;

		std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers() const override;
		std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers(CubA4::system::IIdentityiMap::IdType blockId) const override;

		std::vector<std::shared_ptr<IChunkBBaseContainer>> getChunkBContainers();
		std::vector<std::shared_ptr<IChunkBBaseContainer>> getChunkBContainers(CubA4::system::IIdentityiMap::IdType blockId);

		bool hasBlocksAt(world::BlockInChunkPos pos) const override;
		bool hasBlocksAt(uint32_t index) const override;

		std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const override;
		CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const override;

		std::vector<CubA4::world::BlockAt> getBlocksAt(uint32_t index) const override;
		CubA4::world::BlockAt getBlockAt(uint32_t index, world::Layer layer) const override;

		DataProvider &getDataProvider();
		const IDataProvider &getDataProvider() const override;

		void addContainer(std::shared_ptr<IChunkBBaseContainer> container);
		void removeContainer(size_t idContainer);

		size_t allocateIdContainer();
	protected:
		void onContainerAdded(std::shared_ptr<const IChunkBBaseContainer> container);
		void onContainerRemoved(std::shared_ptr<const IChunkBBaseContainer> container);
	private:
		const CubA4::world::ChunkPos chunkPos_;
		DataProvider dataProvider_;
		std::vector<std::shared_ptr<IChunkBBaseContainer>> containers_;

		// used blocks cache (map BlockId -> use count)
		std::map<CubA4::system::IIdentityiMap::IdType, uint32_t> usedBlocks_;

		size_t genId_ = 0;
	};
}
