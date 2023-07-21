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
		explicit Chunk(const CubA4::world::ChunkPos &chunkPos);
		~Chunk();
		const CubA4::world::ChunkPos &getChunkPos() const override;
		std::vector<std::shared_ptr<const CubA4::object::IBlock>> getUsedBlocks() const override;

		std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers() const override;
		std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock) const override;

		std::vector<std::shared_ptr<IChunkBBaseContainer>> getChunkBContainers();
		std::vector<std::shared_ptr<IChunkBBaseContainer>> getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock);

		bool hasBlocksAt(world::BlockInChunkPos pos) const override;
		bool hasBlocksAt(uint32_t index) const override;
		std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const override;
		CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const override;

		DataProvider &getDataProvider();
		const IDataProvider &getDataProvider() const override;

		void addContainer(std::shared_ptr<IChunkBBaseContainer> container);
		void removeContainer(size_t idContainer);
	protected:
		void onContainerAdded(std::shared_ptr<const IChunkBBaseContainer> container);
		void onContainerRemoved(std::shared_ptr<const IChunkBBaseContainer> container);
	private:
		const CubA4::world::ChunkPos chunkPos_;
		DataProvider dataProvider_;
		std::vector<std::shared_ptr<IChunkBBaseContainer>> containers_;

		// used blocks cache
		std::map<std::shared_ptr<const CubA4::object::IBlock>, uint32_t> usedBlocks;
	};
}
