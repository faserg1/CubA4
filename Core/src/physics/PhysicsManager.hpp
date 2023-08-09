#pragma once

#include <memory>
#include <vector>
#include <physics/IPhysicsManager.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <Core.hpp>

namespace CubA4
{
	class Core;
}

namespace CubA4::physics
{
	class PhysicsWorld;

	class PhysicsManager : public virtual IPhysicsManager
	{
	public:
		PhysicsManager(CubA4::Core &core);
		~PhysicsManager();

		std::unique_ptr<PhysicsWorld> addPhysicsWorld(const IPhysicsDefinition &definition);

		void requestApplyForce(CubA4::object::IEntity &entity) override;

		void iterate(float delta);
		
		void onWorldCreated(PhysicsWorld *world);
		void onWorldDeleted(PhysicsWorld *world);
	private:
		CubA4::Core &core_;
		std::shared_ptr<btDefaultCollisionConfiguration> collisionConfig_;
		std::shared_ptr<btCollisionDispatcher> collisionDispatcher_;
		std::shared_ptr<btBroadphaseInterface> broadphase_;
		std::shared_ptr<btConstraintSolver> contraintsSolver_;

		std::vector<PhysicsWorld*> worlds_;
	};
}