#ifndef WORLD_HPP
#define WORLD_HPP

#include <world/IWorld.hpp>
#include <world/IChunk.hpp>
#include <vector>
#include <unordered_map>
#include "../util/ChunkPosHash.hpp"
#include "../util/SubscriptionHelper.hpp"

namespace CubA4
{
	namespace world
	{
		class Chunk;

		class World :
			public virtual CubA4::mod::world::IWorld
		{
		public:
			explicit World(std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition);
			~World();

			std::string getId() const override;
			std::wstring getName() const override;

			std::shared_ptr<CubA4::core::util::ISubscription> subscribe(CubA4::mod::world::IWorldSubscriber *subscriber) override;

			std::shared_ptr<const CubA4::mod::world::IWorldDefinition> getWorldDefinition() const override;

			void placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, const std::vector<CubA4::mod::world::BlockGlobalPos> positions) override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition_;
			CubA4::core::util::SubscriptionHelper< CubA4::mod::world::IWorldSubscriber> subscriptionHelper_;
			std::unordered_map<const CubA4::mod::world::ChunkPos, std::shared_ptr<CubA4::world::Chunk>, CubA4::core::util::ChunkPosHash> loadedChunks_;
		private:
			void resolve(const CubA4::mod::world::BlockGlobalPos &globalPos, CubA4::mod::world::ChunkPos &chunkPos, CubA4::mod::world::BlockInChunkPos &blockPos);
			std::shared_ptr<CubA4::world::Chunk> findChunk(const CubA4::mod::world::ChunkPos &chunkPos);
		};
	}
}

#endif // WORLD_HPP
