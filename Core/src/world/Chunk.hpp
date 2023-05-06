#pragma once

#include <world/IChunk.hpp>
#include <world/ChunkBRange.hpp>
#include <world/ChunkBSet.hpp>
#include <world/ChunkBMulti.hpp>
#include <world/DataProvider.hpp>
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

		std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const override;
		CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const override;

		DataProvider &getDataProvider();
		const DataProvider &getDataProvider() const;

		// temp
		void addRange(std::shared_ptr<ChunkBRange> container);
	protected:
		void onContainerAdded(std::shared_ptr<const IChunkBBaseContainer> container);
		void onContainerRemoved(std::shared_ptr<const IChunkBBaseContainer> container);
	private:
		const CubA4::world::ChunkPos chunkPos_;
		std::vector<std::shared_ptr<ChunkBRange>> chunkBRanges_;
		std::vector<std::shared_ptr<ChunkBSet>> chunkBSets_;
		std::vector<std::shared_ptr<ChunkBMulti>> chunkBMultis_;

		DataProvider dataProvider_;

		// used blocks cache
		std::map<std::shared_ptr<const CubA4::object::IBlock>, uint32_t> usedBlocks;
	};
}
