#ifndef CORE_CHUNK_HPP
#define CORE_CHUNK_HPP

#include <world/IChunk.hpp>
#include <vector>
#include <map>
#include <atomic>

namespace CubA4
{
	namespace world
	{
		struct UsedBlockInfo
		{
			std::shared_ptr<const CubA4::mod::object::IBlock> block;
			std::vector<CubA4::mod::world::BlockInChunkPos> chunkPositions;
		};

		class Chunk :
			public virtual CubA4::mod::world::IChunk
		{
		public:
			explicit Chunk(const CubA4::mod::world::ChunkPos &chunkPos);
			~Chunk();

			std::vector<std::shared_ptr<const CubA4::mod::object::IBlock>> getUsedBlocks() const override;
			std::vector<CubA4::mod::world::BlockInChunkPos> getChunkPositions(const std::shared_ptr<const CubA4::mod::object::IBlock> usedBlock) const override;
			const CubA4::mod::world::ChunkPos &getChunkPos() const override;

			void placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, std::vector<CubA4::mod::world::BlockInChunkPos> positions);
		protected:
		private:
			std::vector<std::shared_ptr<const CubA4::mod::object::IBlock>> usedBlocks_;
			std::map<std::string, UsedBlockInfo> usedBlockInfos_;
			mutable std::atomic_bool globalLock_;
			const CubA4::mod::world::ChunkPos chunkPos_;
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

#endif // CORE_CHUNK_HPP
