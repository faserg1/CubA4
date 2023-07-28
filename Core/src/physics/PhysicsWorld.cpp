#include <physics/PhysicsWorld.hpp>
#include <physics/PhysicsManager.hpp>
using namespace CubA4::physics;

PhysicsWorld::PhysicsWorld(PhysicsManager &manager, std::unique_ptr<btDiscreteDynamicsWorld> &&dynamicWorld) :
	manager_(manager), dynamicWorld_(std::move(dynamicWorld))
{
	manager_.onWorldCreated(this);
}

PhysicsWorld::~PhysicsWorld()
{
	manager_.onWorldDeleted(this);
}

btDiscreteDynamicsWorld *PhysicsWorld::getWorld()
{
	return dynamicWorld_.get();
}