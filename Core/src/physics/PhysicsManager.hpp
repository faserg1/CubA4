#pragma once

#include <memory>
#include <vector>
#include <physics/IPhysicsManager.hpp>
#include <bullet/btBulletDynamicsCommon.h>

namespace CubA4::physics
{
	class PhysicsWorld;

	class PhysicsManager : public virtual IPhysicsManager
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		std::unique_ptr<IPhysicsWorld> addPhysicsWorld(const IPhysicsDefinition &definition) override;

		void iterate(float delta);
		
		void onWorldCreated(PhysicsWorld *world);
		void onWorldDeleted(PhysicsWorld *world);
	private:
		std::shared_ptr<btDefaultCollisionConfiguration> collisionConfig_;
		std::shared_ptr<btCollisionDispatcher> collisionDispatcher_;
		std::shared_ptr<btBroadphaseInterface> broadphase_;
		std::shared_ptr<btConstraintSolver> contraintsSolver_;

		std::vector<PhysicsWorld*> worlds_;
	};
}