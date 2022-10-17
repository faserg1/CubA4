#pragma once

#include <world/IChunk.hpp>
#include <memory>
#include <vector>
#include <map>
#include <atomic>

namespace CubA4
{
	namespace world
	{
		class ChunkRange;

		class Chunk :
			public virtual CubA4::mod::world::IChunk
		{
		public:
			explicit Chunk(const CubA4::core::world::ChunkPos &chunkPos);
			~Chunk();
			const CubA4::core::world::ChunkPos &getChunkPos() const override;
			std::vector<std::shared_ptr<const CubA4::mod::object::IBlock>> getUsedBlocks() const override;
			std::vector<std::shared_ptr<const CubA4::mod::world::IChunkRange>> getChunkRanges(const std::shared_ptr<const CubA4::mod::object::IBlock> usedBlock) const override;

			void addChunkRange(std::shared_ptr<ChunkRange> chunkRange);
		protected:
		private:
			mutable std::atomic_bool globalLock_;
			const CubA4::core::world::ChunkPos chunkPos_;
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
}

