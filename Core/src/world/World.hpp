#ifndef CORE_WORLD_HPP
#define CORE_WORLD_HPP

#include <world/IWorld.hpp>
#include <world/IChunk.hpp>
#include <vector>
#include <unordered_map>
#include "../util/ChunkPosHash.hpp"
#include <util/SubscriptionHelper.hpp>

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

			std::unique_ptr<CubA4::core::util::ISubscription> subscribe(CubA4::mod::world::IWorldSubscriber *subscriber) const override;

			void test(std::shared_ptr<const CubA4::mod::object::IBlock> block) override;

			std::shared_ptr<const CubA4::mod::world::IWorldDefinition> getWorldDefinition() const override;
			std::vector<std::shared_ptr<const CubA4::mod::world::IChunk>> getChunks() const override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition_;
			mutable CubA4::core::util::SubscriptionHelper<CubA4::mod::world::IWorldSubscriber> subscriptionHelper_;
			std::unordered_map<const CubA4::mod::world::ChunkPos, std::shared_ptr<CubA4::world::Chunk>, CubA4::core::util::ChunkPosHash> loadedChunks_;
		private:
			std::shared_ptr<CubA4::world::Chunk> findChunk(const CubA4::mod::world::ChunkPos &chunkPos);
		};
	}
}

#endif // CORE_WORLD_HPP
