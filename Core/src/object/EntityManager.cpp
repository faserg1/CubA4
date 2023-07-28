#include <object/EntityManager.hpp>
#include <object/EntityFactory.hpp>

using namespace CubA4::object;

EntityManager::EntityManager() = default;

std::shared_ptr<IEntityFactory> EntityManager::registerEntity(IdType factoryId, std::unique_ptr<const IEntityDefinition> &&def)
{
	auto factory = std::make_shared<EntityFactory>(factoryId, std::move(def), registry_);
	return factory;
}