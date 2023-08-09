#include <physics/PhysicsWorld.hpp>
#include <physics/PhysicsManager.hpp>
#include <world/Dimension.hpp>
#include <physics/ChunkCollision.hpp>
#include <physics/DebugRender.hpp>
#include <object/EntityManager.hpp>
#include <object/components/PhysicalBody.hpp>
#include <future>
#include <chrono>
using namespace CubA4::physics;

PhysicsWorld::PhysicsWorld(CubA4::Core &core, PhysicsManager &manager, std::unique_ptr<btDiscreteDynamicsWorld> &&dynamicWorld) :
	core_(core), manager_(manager), dynamicWorld_(std::move(dynamicWorld))
{
	manager_.onWorldCreated(this);

	if (auto renderManager = core.getRenderManager())
	{
		debugRender_ = std::make_unique<DebugRender>(renderManager.get());
		debugRender_->setDebugMode(btIDebugDraw::DBG_DrawWireframe | btIDebugDraw::DBG_DrawAabb | btIDebugDraw::DBG_DrawNormals);
		dynamicWorld_->setDebugDrawer(debugRender_.get());
	}

	if (auto entityManager = core.getEntityManager())
	{
		auto &registry = entityManager->getRegistry();
		added_ = registry.on_construct<CubA4::object::PhysicalBody>().connect<&PhysicsWorld::onPhysicalBodyAdded>(this);
		removed_ = registry.on_destroy<CubA4::object::PhysicalBody>().connect<&PhysicsWorld::onPhysicalBodyRemoved>(this);
	}

	/*static auto future = std::async(std::launch::async, [this]()
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(10s);

		dynamicWorld_->debugDrawWorld();
	});*/
}

PhysicsWorld::~PhysicsWorld()
{
	dynamicWorld_->setDebugDrawer(nullptr);
	manager_.onWorldDeleted(this);
}

void PhysicsWorld::init(CubA4::world::Dimension &dimension)
{
	dimensionSubscription_ = dimension.subscribe(this);
	dimension_ = &dimension;
}

btDiscreteDynamicsWorld *PhysicsWorld::getWorld()
{
	return dynamicWorld_.get();
}

void PhysicsWorld::onLoadedChunksUpdated()
{
	for (auto chunk : dimension_->getChunks())
	{
		auto chunkCollision = std::make_shared<ChunkCollision>(core_, chunk, *dynamicWorld_);
		chunkCollisions_.insert_or_assign(chunk->getChunkPos(), chunkCollision);
	}
}

void PhysicsWorld::onPhysicalBodyAdded(entt::registry &registry, entt::entity entity)
{
	// TODO: filter world by id
	auto &physBody = registry.get<CubA4::object::PhysicalBody>(entity);
	dynamicWorld_->addRigidBody(physBody.collisionObject.get());
}

void PhysicsWorld::onPhysicalBodyRemoved(entt::registry &registry, entt::entity entity)
{
	auto &physBody = registry.get<CubA4::object::PhysicalBody>(entity); 
	dynamicWorld_->removeRigidBody(physBody.collisionObject.get());
}