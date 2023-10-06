#include <object/Entity.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/RenderInfoComponent.hpp>
#include <object/components/Types.hpp>
#include <object/components/CameraComponent.hpp>
#include <object/components/ControllerComponent.hpp>

using namespace CubA4::object;

Entity::Entity(entt::registry &registry, entt::entity entity) :
	registry_(registry), entity_(entity)
{
	
}

Entity::~Entity()
{
	forceDestroy();
}

Entity::IdType Entity::getEntityId() const
{
	return registry_.get<WorldInfo>(entity_).entityId;
}

Entity::IdType Entity::getFactoryId() const
{
	return registry_.get<WorldInfo>(entity_).factoryId;
}

entt::registry &Entity::getRegistry() const
{
	return registry_;
}

entt::entity Entity::getEntity() const
{
	return entity_;
}

CameraComponent *Entity::getCameraComponent()
{
	return registry_.try_get<CameraComponent>(entity_);
}

const WorldInfo *Entity::getWorldInfoComponent() const
{
	return &registry_.get<WorldInfo>(entity_);
}

void Entity::forceDestroy()
{
	if (!registry_.valid(entity_))
		return;
	RemoveFirst<EntityContextActions, RenderInfoComponent>::remove(registry_, entity_);
	registry_.destroy(entity_);
	entity_ = entt::tombstone;
}

void Entity::enableControls()
{
	controlsEnabled_ = true;
	if (auto controller = registry_.try_get<ControllerComponent>(entity_))
		controller->actions->requestContextCheck();
}

void Entity::disableControls()
{
	controlsEnabled_ = false;
	if (auto controller = registry_.try_get<ControllerComponent>(entity_))
		controller->actions->requestContextCheck();
}

bool Entity::isControlsEnabled() const
{
	return controlsEnabled_;
}