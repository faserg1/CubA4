#ifndef WORLD_HPP
#define WORLD_HPP

#include <world/IWorld.hpp>
#include <vector>

namespace CubA4
{
	namespace world
	{
		class World :
			public virtual CubA4::mod::world::IWorld
		{
		public:
			explicit World(std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition);
			~World();

			std::string getId() const override;
			std::wstring getName() const override;

			void subscribe(CubA4::mod::world::IWorldSubscriber *subscriber) override;
			void unsubscribe(CubA4::mod::world::IWorldSubscriber *subscriber) override;

			std::shared_ptr<const CubA4::mod::world::IWorldDefinition> getWorldDefinition() const override;

			void placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, std::vector<CubA4::mod::world::BlockGlobalPos> positions) override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition_;
			std::vector<CubA4::mod::world::IWorldSubscriber*> subscribers_;
		private:
			void resolve(const CubA4::mod::world::BlockGlobalPos &globalPos, CubA4::mod::world::ChunkPos &chunkPos, CubA4::mod::world::BlockInChunkPos &blockPos);
		};
	}
}

#endif // WORLD_HPP
