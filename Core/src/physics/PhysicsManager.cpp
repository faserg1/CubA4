#include <physics/PhysicsManager.hpp>
#include <physics/PhysicsWorld.hpp>
#include <object/Entity.hpp>
using namespace CubA4::physics;

PhysicsManager::PhysicsManager(Core &core) :
	core_(core),
	collisionConfig_(std::make_shared<btDefaultCollisionConfiguration>()),
	collisionDispatcher_(std::make_shared<btCollisionDispatcher>(collisionConfig_.get())),
	broadphase_(std::make_shared<btDbvtBroadphase>()),
	contraintsSolver_(std::make_shared<btSequentialImpulseConstraintSolver>())
{

}

PhysicsManager::~PhysicsManager()
{

}

std::unique_ptr<PhysicsWorld> PhysicsManager::addPhysicsWorld(const IPhysicsDefinition &definition)
{
	auto physicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
		collisionDispatcher_.get(), broadphase_.get(), contraintsSolver_.get(), collisionConfig_.get());
	auto defaultGravity = definition.getDefaultGravity();
	physicsWorld->setGravity({defaultGravity.x, defaultGravity.y, defaultGravity.z});
	return std::make_unique<PhysicsWorld>(core_, *this, std::move(physicsWorld));
}

void PhysicsManager::requestApplyForce(CubA4::object::IEntity &iEntity)
{
	auto *entity = dynamic_cast<CubA4::object::Entity*>(&iEntity);

}

void PhysicsManager::iterate(float delta)
{
	for (auto world : worlds_)
		world->getWorld()->stepSimulation(delta);
}

void PhysicsManager::onWorldCreated(PhysicsWorld *world)
{
	// TODO: Debug assert?
	worlds_.push_back(world);
}

void PhysicsManager::onWorldDeleted(PhysicsWorld *world)
{
	if (auto it = std::find(worlds_.begin(), worlds_.end(), world); it != worlds_.end())
		worlds_.erase(it);
}