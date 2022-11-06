#pragma once

#include <world/IChunk.hpp>
#include <world/ChunkRange.hpp>
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
		std::vector<std::shared_ptr<const CubA4::world::IChunkRange>> getChunkRanges() const override;
		std::vector<std::shared_ptr<const CubA4::world::IChunkRange>> getChunkRanges(const std::shared_ptr<const CubA4::object::IBlock> usedBlock) const override;
		std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const override;
		CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const override;

		void addChunkRange(std::shared_ptr<ChunkRange> chunkRange);
	protected:
		
	private:
		mutable std::atomic_bool globalLock_;
		const CubA4::world::ChunkPos chunkPos_;
		std::vector<std::shared_ptr<ChunkRange>> chunkRanges_;
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
