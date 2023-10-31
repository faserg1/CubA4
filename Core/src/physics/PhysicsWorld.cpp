#include <physics/PhysicsWorld.hpp>
#include <physics/PhysicsManager.hpp>
#include <world/Dimension.hpp>
#include <physics/ChunkCollision.hpp>
#include <physics/DebugRender.hpp>
#include <object/EntityManager.hpp>
#include <object/components/PhysicalBody.hpp>
#include <object/components/WorldInfo.hpp>
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

CubA4::world::RayTestResult PhysicsWorld::closestBlockRayTest(CubA4::world::GlobalPosition from, CubA4::world::GlobalPosition to) const
{
	using namespace CubA4::world;
	auto floatFrom = from.globalPos<float>();
	auto floatTo = to.globalPos<float>();
	btVector3 btFrom(floatFrom.x, floatFrom.y, floatFrom.z);
	btVector3 btTo(floatTo.x, floatTo.y, floatTo.z);

	btDiscreteDynamicsWorld::ClosestRayResultCallback result(btFrom, btTo);
	dynamicWorld_->rayTest(btFrom, btTo, result);
	auto target = result.m_hitPointWorld - (result.m_hitNormalWorld / 2);

	// TODO: think about layers
	// TODO: return all the needed information later
	// block hitted (chunk pos?), side hitted, actual hit position, normal, 
	// TODO: simulations islands???

	const auto blockPos = BlockInChunkPos
	{
		static_cast<decltype(BlockInChunkPos::x)>(std::floor(target.x())),
		static_cast<decltype(BlockInChunkPos::y)>(std::floor(target.y())),
		static_cast<decltype(BlockInChunkPos::z)>(std::floor(target.z())),
	};

	GlobalPosition globalPosition(blockPos);

	return CubA4::world::RayTestResult
	{
		.chunkPos = globalPosition.chunkPos(),
		.blockPos = globalPosition.blockPosition()
		// pass the side
	};
}

btDiscreteDynamicsWorld *PhysicsWorld::getWorld()
{
	return dynamicWorld_.get();
}

void PhysicsWorld::stepSimulation(float delta)
{
	auto lock = std::unique_lock(accessMutex_);
	dynamicWorld_->stepSimulation(delta);
}

void PhysicsWorld::onLoadedChunksUpdated()
{
	auto lock = std::unique_lock(accessMutex_);
	std::vector<CubA4::world::ChunkPos> addedPositions;
	// TODO: remove unused chunks
	for (auto chunk : dimension_->getChunks())
	{
		tf::Taskflow chunkCompilation;
		
		auto chunkCollision = std::make_shared<ChunkCollision>(core_, chunk, *dynamicWorld_, chunkCompilation);

		prepareTaskflowForMutexLock(chunkCompilation);

		chunkCollisions_.insert_or_assign(chunk->getChunkPos(), chunkCollision);
		addedPositions.push_back(chunk->getChunkPos());

		exec_.run(std::move(chunkCompilation));
	}

	// make diff between addedPosition and what we have now. delete that is not in addedPositions
}

void PhysicsWorld::onChunkUpdated(const CubA4::world::ChunkPos &chunkPos)
{
	auto lock = std::unique_lock(accessMutex_);
	auto chunk = dimension_->findChunk(chunkPos);
	tf::Taskflow chunkCompilation;

	auto chunkCollision = std::make_shared<ChunkCollision>(core_, chunk, *dynamicWorld_, chunkCompilation);

	prepareTaskflowForMutexLock(chunkCompilation);

	chunkCollisions_.insert_or_assign(chunk->getChunkPos(), chunkCollision);

	exec_.run(std::move(chunkCompilation));
}

void PhysicsWorld::onPhysicalBodyAdded(entt::registry &registry, entt::entity entity)
{
	auto lock = std::unique_lock(accessMutex_);
	// TODO: filter world by id
	auto &worldInfo = registry.get<CubA4::object::WorldInfo>(entity);
	auto &physBody = registry.get<CubA4::object::PhysicalBody>(entity);
	dynamicWorld_->addRigidBody(physBody.collisionObject.get());
}

void PhysicsWorld::onPhysicalBodyRemoved(entt::registry &registry, entt::entity entity)
{
	auto lock = std::unique_lock(accessMutex_);
	auto &physBody = registry.get<CubA4::object::PhysicalBody>(entity); 
	dynamicWorld_->removeRigidBody(physBody.collisionObject.get());
}

void PhysicsWorld::prepareTaskflowForMutexLock(tf::Taskflow &flow)
{
	std::vector<tf::Task> tasks;

	flow.for_each_task([&tasks](tf::Task task){
		tasks.push_back(task);
	});

	auto lockMutexTask = flow.emplace([this]()
	{
		accessMutex_.lock();
	});
	auto unlockMutexTask = flow.emplace([this]()
	{
		accessMutex_.unlock();
	});

	for (auto &task : tasks)
	{
		// if marked to be synced
		if (task.data())
		{
			task.succeed(lockMutexTask);
			task.precede(unlockMutexTask);
		}
		else
		{
			task.precede(lockMutexTask);
		}
	}
}