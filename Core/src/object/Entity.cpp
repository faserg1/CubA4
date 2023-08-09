#include <object/Entity.hpp>
#include <object/components/WorldInfo.hpp>
using namespace CubA4::object;

Entity::Entity(entt::registry &registry, entt::entity entity) :
	registry_(registry), entity_(entity)
{
	
}

Entity::~Entity()
{
	registry_.destroy(entity_);
}

Entity::IdType Entity::getEntityId() const
{
	return registry_.get<WorldInfo>(entity_).entityId;
}

Entity::IdType Entity::getFactoryId() const
{
	return registry_.get<WorldInfo>(entity_).factoryId;
}

entt::entity Entity::getEntity() const
{
	return entity_;
}