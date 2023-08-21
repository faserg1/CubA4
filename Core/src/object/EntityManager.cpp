#include <Core.hpp>
#include <object/EntityManager.hpp>
#include <object/EntityFactory.hpp>
#include <object/EntityFactoryBuilder.hpp>
#include <object/EntityRenderBuilder.hpp>
#include <object/EntityBuilderData.hpp>

using namespace CubA4::object;

EntityManager::EntityManager(CubA4::Core &core) :
	core_(core), entityRenderManager_(createRenderManager())
{

}

std::shared_ptr<IEntityFactory> EntityManager::registerEntity(IdType factoryId, std::unique_ptr<const IEntityDefinition> &&def)
{
	EntityBuilderData data;

	{
		auto factoryBuilder = std::make_unique<EntityFactoryBuilder>(data);
		def->onComponentStage(*factoryBuilder);
	}
	

	if (core_.getApplicationFlags() & CubA4::ApplicationFlag::Render)
	{
		auto renderBuilder = std::make_unique<EntityRenderBuilder>(data);
		def->onRenderPrepareStage(*renderBuilder);
	}
	auto factory = std::make_shared<EntityFactory>(factoryId, std::move(def), registry_, data);
	return factory;
}

entt::registry &EntityManager::getRegistry()
{
	return registry_;
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