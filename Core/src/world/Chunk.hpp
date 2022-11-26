#pragma once

#include <world/IChunk.hpp>
#include <world/ChunkRange.hpp>
#include <world/ChunkBRange.hpp>
#include <world/ChunkBSet.hpp>
#include <world/ChunkBMulti.hpp>
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

		std::vector<std::shared_ptr<const CubA4::world::IChunkRange>> getChunkRanges() const override;
		std::vector<std::shared_ptr<const CubA4::world::IChunkRange>> getChunkRanges(const std::shared_ptr<const CubA4::object::IBlock> usedBlock) const override;
		std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const override;
		CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const override;

		void addBlock(std::shared_ptr<const object::IBlock>, world::BlockInChunkPos at) override;
		void fillWithBlock(std::shared_ptr<const object::IBlock>, world::BlockInChunkPos start, world::BlockInChunkPos end) override;

		void addChunkRange(std::shared_ptr<ChunkRange> chunkRange);
	protected:
		
	private:
		mutable std::atomic_bool globalLock_;
		const CubA4::world::ChunkPos chunkPos_;
		std::vector<std::shared_ptr<ChunkRange>> chunkRanges_;
		std::vector<std::shared_ptr<ChunkBRange>> chunkBRanges_;
		std::vector<std::shared_ptr<ChunkBSet>> chunkBSets_;
		std::vector<std::shared_ptr<ChunkBMulti>> chunkBMultis_;

		// used blocks cache
		
	private:
		class Locker
		{
		public:
			Locker(std::atomic_bool &lock);
			~Locker();
		private:
			std::atomic_bool &lock_;
		};
	};
}
