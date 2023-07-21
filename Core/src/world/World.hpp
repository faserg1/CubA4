#pragma once

#include <Core.hpp>
#include <world/IWorld.hpp>
#include <world/Chunk.hpp>
#include <world/Dimension.hpp>
#include <vector>
#include <unordered_map>
#include <util/ChunkPosHash.hpp>
#include <util/SubscriptionHelper.hpp>

namespace CubA4::world
{
	class World :
		public virtual CubA4::world::IWorld
	{
	public:
		explicit World(Core &core, std::shared_ptr<const CubA4::world::IWorldDefinition> definition);
		~World();

		std::string getId() const override;
		std::wstring getName() const override;

		std::unique_ptr<CubA4::util::ISubscription> subscribe(CubA4::world::IWorldSubscriber *subscriber) const override;

		void test(std::vector<std::shared_ptr<const CubA4::object::IBlock>> blocks) override;

		std::shared_ptr<const CubA4::world::IWorldDefinition> getWorldDefinition() const override;
		std::vector<std::shared_ptr<const CubA4::world::IChunk>> getChunks() const override;

		void addDimension(std::shared_ptr<Dimension> dim);
		std::vector<std::shared_ptr<const IDimension>> getDimensions() const override;
		std::shared_ptr<const IDimension> findDimension(std::string id) const override;
		std::shared_ptr<Dimension> findDimension(std::string id);
	protected:
	private:
		Core &core_;
		const std::shared_ptr<const CubA4::world::IWorldDefinition> definition_;
		mutable CubA4::util::SubscriptionHelper<CubA4::world::IWorldSubscriber> subscriptionHelper_;
		std::unordered_map<const CubA4::world::ChunkPos, std::shared_ptr<CubA4::world::Chunk>, CubA4::util::ChunkPosHash> loadedChunks_;

		std::unordered_map<std::string, std::shared_ptr<Dimension>> dimensions_;
	private:
		std::shared_ptr<CubA4::world::Chunk> findChunk(const CubA4::world::ChunkPos &chunkPos);
	};
}

