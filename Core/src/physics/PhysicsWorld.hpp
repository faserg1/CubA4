#pragma once

#include <memory>
#include <physics/IPhysicsWorld.hpp>
#include <bullet/btBulletDynamicsCommon.h>

namespace CubA4::physics
{
	class PhysicsManager;

	class PhysicsWorld : public virtual IPhysicsWorld
	{
	public:
		PhysicsWorld(PhysicsManager &manager, std::unique_ptr<btDiscreteDynamicsWorld> &&dynamicWorld);
		~PhysicsWorld();

		btDiscreteDynamicsWorld *getWorld();
	private:
		PhysicsManager &manager_;
		std::unique_ptr<btDiscreteDynamicsWorld> dynamicWorld_;
	};
}