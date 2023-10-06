#pragma once

#include <Core.hpp>
#include <world/IDimension.hpp>
#include <world/Chunk.hpp>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <util/ChunkPosHash.hpp>
#include <util/SubscriptionHelper.hpp>
#include <physics/IPhysicsWorld.hpp>
#include <object/Entity.hpp>
#include <util/EntityKeyHash.hpp>

namespace CubA4::world
{
	class World;

	class Dimension : public virtual IDimension
	{
		friend class WorldControl;
		using IdFactoryType = decltype(CubA4::object::WorldInfo::factoryId);
		using IdEntityType = decltype(CubA4::object::WorldInfo::entityId);
		using PairKey = std::pair<IdFactoryType, IdEntityType>;
	public:
		Dimension(Core &core, World &world, const CubA4::world::IDimensionDescription &description, std::unique_ptr<physics::IPhysicsWorld> &&physicalWorld);

		IdType getId() const override;
		std::wstring getName() const override;

		std::unique_ptr<CubA4::util::ISubscription> subscribe(CubA4::world::IDimensionSubscriber *subscriber) const override;

		const CubA4::world::IDimensionDescription &getDimensionDescription() const override;
		std::vector<std::shared_ptr<const IChunk>> getChunks() const override;

		std::vector<CubA4::world::ChunkPos> getLoadedChunks() override;
		std::vector<CubA4::world::ChunkPos> getActiveChunks() override;

		void rayTest(CubA4::world::GlobalPosition from, CubA4::world::GlobalPosition to) const override;

		const IWorld &getWorld() const override;
		World &getWorld();

		void onChunkLoaded(std::shared_ptr<Chunk> chunk);
		void onChunkActived(CubA4::world::ChunkPos position);

		void onChunkUnload(CubA4::world::ChunkPos position);
		void onChunkDeactivated(CubA4::world::ChunkPos position);

		std::shared_ptr<const IChunk> findChunk(CubA4::world::ChunkPos pos) const override;
		std::shared_ptr<Chunk> findChunk(CubA4::world::ChunkPos pos);

		void addEntity(std::shared_ptr<CubA4::object::Entity> entity);
		void removeEntity(const CubA4::object::IEntity &entity);
	private:
		Core &core_;
		World &world_;

		const CubA4::world::IDimensionDescription &description_;
		std::unique_ptr<physics::IPhysicsWorld> physicalWorld_;

		// remove friend and share?
		mutable CubA4::util::SubscriptionHelper<CubA4::world::IDimensionSubscriber> subscriptionHelper_;

		std::unordered_map<const CubA4::world::ChunkPos, std::shared_ptr<CubA4::world::Chunk>, CubA4::util::ChunkPosHash> loadedChunks_;
		std::unordered_set<CubA4::world::ChunkPos, CubA4::util::ChunkPosHash> activeChunks_;

		// TODO: use factory+entity ids
		std::unordered_map<PairKey, std::shared_ptr<CubA4::object::Entity>, CubA4::util::FactoryAndEntityIdHash> entites_;
	};
}



