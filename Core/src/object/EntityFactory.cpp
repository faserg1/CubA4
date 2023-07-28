#include <object/EntityFactory.hpp>
#include <world/GlobalPosition.hpp>
#include <object/components/WorldInfo.hpp>
using namespace CubA4::object;

EntityFactory::EntityFactory(IdFactoryType id, std::unique_ptr<const IEntityDefinition> &&def, entt::registry &registry) :
	id_(id), registry_(registry), def_(std::move(def))
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

std::unique_ptr<Entity> EntityFactory::create()
{
	auto handle = registry_.create();
	registry_.emplace<world::GlobalPosition>(handle);
	registry_.emplace<WorldInfo>(handle);
	registry_.patch<WorldInfo>(handle, [this](auto &worldInfo)
	{
		worldInfo.factoryId = id_;
		worldInfo.entityId = idGenerator_++;
	});
	return std::make_unique<Entity>(registry_, handle);
}