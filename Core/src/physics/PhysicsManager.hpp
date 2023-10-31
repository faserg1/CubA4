#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <atomic>
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
	class PhysicsFactory;

	class PhysicsManager : public virtual IPhysicsManager
	{
	public:
		PhysicsManager(CubA4::Core &core);
		~PhysicsManager();

		std::unique_ptr<PhysicsWorld> addPhysicsWorld(const IWorldPhysicsDefinition &definition);

		void requestApplyForce(CubA4::object::IEntity &entity) override;
		IPhysicsFactory &getPhysicsFactory() const override;


		void start();
		void stop();
		
		void onWorldCreated(PhysicsWorld *world);
		void onWorldDeleted(PhysicsWorld *world);
	private:
		void loop();
	private:
		CubA4::Core &core_;
		std::shared_ptr<btDefaultCollisionConfiguration> collisionConfig_;
		std::shared_ptr<btCollisionDispatcher> collisionDispatcher_;
		std::shared_ptr<btBroadphaseInterface> broadphase_;
		std::shared_ptr<btConstraintSolver> contraintsSolver_;

		std::vector<PhysicsWorld*> worlds_;

		std::unique_ptr<PhysicsFactory> factory_;

		std::thread physicsThread_;
		std::atomic_bool physicsRun_ = false;
	};
}