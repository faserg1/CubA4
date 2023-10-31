#include <Core.hpp>
#include <object/EntityManager.hpp>
#include <object/EntityFactory.hpp>
#include <object/EntityFactoryBuilder.hpp>
#include <object/EntityRenderBuilder.hpp>
#include <object/EntityBuilderData.hpp>
#include <object/IEntityHandler.hpp>

#include <object/components/WorldInfo.hpp>
#include <object/components/InternalEntityInfo.hpp>
#include <object/components/Transform.hpp>
#include <object/components/HandlerComponent.hpp>

#include <world/World.hpp>
#include <world/Dimension.hpp>

using namespace CubA4::object;

EntityManager::EntityManager(CubA4::Core &core) :
	core_(core), entityRenderManager_(createRenderManager())
{
	registerSignals();
}

std::shared_ptr<const CubA4::world::IWorld> EntityManager::getCurrentWorld(IEntity &iEntity) const
{
	auto entity = dynamic_cast<Entity*>(&iEntity);
	if (!entity)
		return nullptr;
	auto &registry = entity->getRegistry();
	auto handle = entity->getEntity();
	auto &worldInfo = registry_.get<WorldInfo>(handle);
	return core_.getEnvironment()->getObjectT<CubA4::world::World>(worldInfo.worldId);
}

std::shared_ptr<const CubA4::world::IDimension> EntityManager::getCurrentDimension(IEntity &iEntity) const
{
	auto entity = dynamic_cast<Entity*>(&iEntity);
	if (!entity)
		return nullptr;
	auto &registry = entity->getRegistry();
	auto handle = entity->getEntity();
	auto &worldInfo = registry_.get<WorldInfo>(handle);
	return core_.getEnvironment()->getObjectT<CubA4::world::Dimension>(worldInfo.dimensionId);
}

std::shared_ptr<IEntityFactory> EntityManager::registerEntity(IdType factoryId, std::unique_ptr<const IEntityDefinition> &&def)
{
	EntityBuilderData data {};

	{
		auto factoryBuilder = std::make_unique<EntityFactoryBuilder>(data);
		def->onComponentStage(*factoryBuilder);
	}
	

	if (core_.getApplicationFlags() & CubA4::ApplicationFlag::Render)
	{
		auto renderBuilder = std::make_unique<EntityRenderBuilder>(data);
		def->onRenderPrepareStage(*renderBuilder);
	}
	// TODO: fill the managers
	EntityFactory::Managers managers
	{
		.renderManager = core_.getRenderManager(),
		.controller = core_.getGame()->getController()
	};
	auto factory = std::make_shared<EntityFactory>(factoryId, std::move(def), registry_, data, managers);
	return factory;
}

entt::registry &EntityManager::getRegistry()
{
	return registry_;
}

void EntityManager::iterate()
{

}

EntityRenderManager &EntityManager::getEntityRenderManager()
{
	return *entityRenderManager_;
}

std::unique_ptr<EntityRenderManager> EntityManager::createRenderManager()
{
	std::unique_ptr<EntityRenderManager> manager;
	if (core_.getApplicationFlags() & CubA4::ApplicationFlag::Render)
		manager = std::make_unique<EntityRenderManager>(registry_) ;
	return manager;
}

void EntityManager::registerSignals()
{
	onEntityUpdated_ = registry_.on_update<Transform>().connect<&EntityManager::onEntityUpdated>(this);
}

void EntityManager::onEntityUpdated(entt::registry &registry, entt::entity entity)
{
	if (auto handlerComponent = registry.try_get<HandlerComponent>(entity))
	{
		auto [internal, tr] = registry.get<InternalEntityInfo, Transform>(entity);
		auto handler = handlerComponent->handler.lock();
		if (!handler)
		{
			registry.remove<HandlerComponent>(entity);
			return;
		}
		handler->onTransformChanged(*internal.entity.lock(), tr);
	}
}