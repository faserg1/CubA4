#include <object/EntityFactory.hpp>
#include <object/EntityControllerRules.hpp>
#include <object/components/Transform.hpp>
#include <object/components/InternalEntityInfo.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/RenderInfoComponent.hpp>
#include <object/components/PhysicalBody.hpp>
#include <object/components/CameraComponent.hpp>
#include <object/components/ControllerComponent.hpp>
#include <physics/IPhysicsEntityDefinition.hpp>
#include <physics/BoxCollisionBodyDefinition.hpp>

#include <engine/IRenderManager.hpp>
#include <engine/world/IWorldManager.hpp>
#include <game/controller/IController.hpp>

using namespace CubA4::object;

EntityFactory::EntityFactory(IdFactoryType id, std::unique_ptr<const IEntityDefinition> &&def,
	entt::registry &registry, EntityBuilderData &data, Managers managers) :
	id_(id), registry_(registry), def_(std::move(def)), data_(data), managers_(managers)
{
	
}

EntityFactory::IdType EntityFactory::getId() const
{
	return def_->getId();
}

std::wstring EntityFactory::getName() const
{
	return def_->getName();
}

std::shared_ptr<Entity> EntityFactory::create(IdWorldType idWorld, IdWorldType idDimension,
	const CubA4::world::GlobalPosition &pos) const
{
	auto handle = registry_.create();
	auto entity = std::make_shared<Entity>(registry_, handle);
	registry_.emplace<Transform>(handle, pos);
	registry_.emplace<WorldInfo>(handle);
	registry_.emplace<InternalEntityInfo>(handle, entity);

	// TODO: connect to handler?

	registry_.patch<WorldInfo>(handle, [this, idWorld, idDimension](auto &worldInfo)
	{
		worldInfo.factoryId = id_;
		worldInfo.entityId = idGenerator_++;
		worldInfo.worldId = idWorld;
		worldInfo.dimensionId = idDimension;
	});
	if (data_.renderModel)
	{
		registry_.emplace<RenderInfoComponent>(handle, data_.renderModel);
	}
	if (data_.physicsDefinition)
	{
		preparePhysics(handle, *data_.physicsDefinition);
	}

	if (data_.attachCamera && !managers_.renderManager.expired())
	{
		auto worldManager = managers_.renderManager.lock()->getWorldManager();
		auto camera = worldManager->createCamera();
		registry_.emplace<CameraComponent>(handle, camera);
	}

	if (data_.controllerFactory && !managers_.controller.expired())
	{
		auto controller = managers_.controller.lock();
		auto entityRules = std::make_unique<EntityControllerRules>(entity, data_.controllerRules);
		auto contextActionsEntity = controller->getRootActions()->addContextActions(std::move(entityRules), std::make_tuple<EntityArg>(entity));
		data_.controllerFactory(*contextActionsEntity);
		registry_.emplace<ControllerComponent>(handle, contextActionsEntity);
	}

	return entity;
}

void EntityFactory::preparePhysics(entt::entity handle, const CubA4::physics::IPhysicsEntityDefinition &def) const
{
	using namespace CubA4::physics;

	auto bodyOffset = def.getCollisonBody()->getOffset();

	btTransform tr {};
	tr.setIdentity();
	tr.setOrigin(btVector3{bodyOffset.x, bodyOffset.y, bodyOffset.z});

	PhysicalBody body;

	switch (def.getCollisonBody()->getType())
	{
		case BodyType::Box:
		{
			auto boxDef = std::dynamic_pointer_cast<const BoxCollisionBodyDefinition>(def.getCollisonBody());
			auto halfExtents = boxDef->getHalfExtents();
			body.shape = std::make_unique<btBoxShape>(btVector3{halfExtents.x, halfExtents.y, halfExtents.z});
			break;
		}
		default:
		{
			// TODO: log
			return;
		}
	}

	
	body.offsetShape = std::make_unique<btCompoundShape>();
	body.offsetShape->addChildShape(tr, body.shape.get());
	body.motionState = std::make_unique<MotionState>(registry_, handle);
	body.collisionObject = std::make_unique<btRigidBody>(def.getMass(), body.motionState.get(), body.offsetShape.get());
	body.collisionObject->activate();
	registry_.emplace<PhysicalBody>(handle, std::move(body));
}