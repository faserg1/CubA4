#include <object/EntityFactory.hpp>
#include <object/components/Transform.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/RenderInfoComponent.hpp>
#include <object/components/PhysicalBody.hpp>
using namespace CubA4::object;

EntityFactory::EntityFactory(IdFactoryType id, std::unique_ptr<const IEntityDefinition> &&def, entt::registry &registry, const EntityBuilderData &data) :
	id_(id), registry_(registry), def_(std::move(def)), data_(data)
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
	registry_.emplace<Transform>(handle, pos);
	registry_.emplace<WorldInfo>(handle);
	registry_.patch<WorldInfo>(handle, [this, idWorld, idDimension](auto &worldInfo)
	{
		worldInfo.factoryId = id_;
		worldInfo.entityId = idGenerator_++;
		worldInfo.worldId = idWorld;
		worldInfo.dimensionId = idDimension;
	});
	// TODO: Check for render info
	if (true)
	{
		registry_.emplace<RenderInfoComponent>(handle, data_.renderModel);
	}
	// TODO: Check for physics info
	if (true)
	{
		// TODO: take offfset from somewhere else
		btTransform tr {};
		tr.setIdentity();
		tr.setOrigin(btVector3{0.5, 0.5, 0.5});

		PhysicalBody body;
		body.shape = std::make_unique<btBoxShape>(btVector3{0.5f, 0.5f, 0.5f});
		body.offsetShape = std::make_unique<btCompoundShape>();
		body.offsetShape->addChildShape(tr, body.shape.get());
		body.motionState = std::make_unique<MotionState>(registry_, handle);
		body.collisionObject = std::make_unique<btRigidBody>(1.f, body.motionState.get(), body.offsetShape.get());
		body.collisionObject->activate();
		registry_.emplace<PhysicalBody>(handle, std::move(body));
	}
	return std::make_shared<Entity>(registry_, handle);
}