#include <physics/PhysicsManager.hpp>
#include <physics/PhysicsWorld.hpp>
#include <physics/PhysicsFactory.hpp>
#include <object/Entity.hpp>
using namespace CubA4::physics;

PhysicsManager::PhysicsManager(Core &core) :
	core_(core),
	collisionConfig_(std::make_shared<btDefaultCollisionConfiguration>()),
	collisionDispatcher_(std::make_shared<btCollisionDispatcher>(collisionConfig_.get())),
	broadphase_(std::make_shared<btDbvtBroadphase>()),
	contraintsSolver_(std::make_shared<btSequentialImpulseConstraintSolver>()),
	factory_(std::move(std::make_unique<PhysicsFactory>()))
{

}

PhysicsManager::~PhysicsManager()
{

}

std::unique_ptr<PhysicsWorld> PhysicsManager::addPhysicsWorld(const IWorldPhysicsDefinition &definition)
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

IPhysicsFactory &PhysicsManager::getPhysicsFactory() const
{
	return *factory_;
}

void PhysicsManager::start()
{
	physicsRun_ = true;
	physicsThread_ = std::thread(&PhysicsManager::loop, this);
}

void PhysicsManager::stop()
{
	physicsRun_ = false;
	physicsThread_.join();
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

void PhysicsManager::loop()
{
	using namespace std::chrono_literals;
	using Clock = std::chrono::steady_clock;
	using FloatSeconds = std::chrono::duration<float>;
	auto last = Clock::now();
	while (physicsRun_)
	{
		std::this_thread::sleep_until(last + 1s / 60);
		auto current = Clock::now();
		auto interval = current - last;
		last = current;
		auto delta = std::chrono::duration_cast<FloatSeconds>(interval).count();
		for (auto world : worlds_)
			world->stepSimulation(delta);
	}
}