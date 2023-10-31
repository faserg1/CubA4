#pragma once

#include <memory>
#include <unordered_map>
#include <physics/IPhysicsWorld.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <util/ISubscription.hpp>
#include <util/ChunkPosHash.hpp>
#include <world/IDimensionSubscriber.hpp>
#include <Core.hpp>
#include <entt/entt.hpp>
#include <taskflow/taskflow.hpp>
#include <mutex>

namespace CubA4::world
{
	class Dimension;
}
namespace CubA4::physics
{
	class PhysicsManager;
	class ChunkCollision;
	class DebugRender;

	class PhysicsWorld :
		public virtual IPhysicsWorld,
		public virtual CubA4::world::IDimensionSubscriber
	{
	public:
		PhysicsWorld(CubA4::Core &core, PhysicsManager &manager, std::unique_ptr<btDiscreteDynamicsWorld> &&dynamicWorld);
		~PhysicsWorld();

		void init(CubA4::world::Dimension &dimension);
		CubA4::world::RayTestResult closestBlockRayTest(CubA4::world::GlobalPosition from, CubA4::world::GlobalPosition to) const override;

		btDiscreteDynamicsWorld *getWorld();
		void stepSimulation(float delta);
	protected:
		void onLoadedChunksUpdated() override;
		void onChunkUpdated(const CubA4::world::ChunkPos &chunkPos) override;

	private:
		void onPhysicalBodyAdded(entt::registry &registry, entt::entity entity);
		void onPhysicalBodyRemoved(entt::registry &registry, entt::entity entity);

		void prepareTaskflowForMutexLock(tf::Taskflow &flow);
	private:
		CubA4::Core &core_;
		PhysicsManager &manager_;
		std::unique_ptr<btDiscreteDynamicsWorld> dynamicWorld_;
		std::unique_ptr<CubA4::util::ISubscription> dimensionSubscription_;
		CubA4::world::Dimension *dimension_;
		std::unordered_map<CubA4::world::ChunkPos, std::shared_ptr<ChunkCollision>, CubA4::util::ChunkPosHash> chunkCollisions_;

		std::unique_ptr<DebugRender> debugRender_;

		entt::connection added_;
		entt::connection removed_;

		std::mutex accessMutex_;
		tf::Executor exec_;
	};
}