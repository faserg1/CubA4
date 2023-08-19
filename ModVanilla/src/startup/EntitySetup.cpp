#include <startup/EntitySetup.hpp>
#include <entities/PlayerDefinition.hpp>

using namespace CubA4::startup;
using namespace CubA4::logging;
using namespace CubA4::resources;
using namespace CubA4::manager;

EntitySetup::EntitySetup()
{

	
}

EntitySetup::~EntitySetup()
{
	
}

void EntitySetup::load(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<ModManager> manager)
{
	core_ = core;
	manager_ = manager;
	log_ = core_->getLogger()->createTaggedLog(LogSourceSystem::Mod, "ModVanilla/RenderStartup");
}

void EntitySetup::preinit(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{

}

void EntitySetup::init(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{
	auto renderManager = manager_->getRenderManager();
	auto entityManager = manager_->getEntityManager();

	auto model = renderManager->getModel("test-cube-player");
	auto playerDef = std::make_unique<object::PlayerDefinition>(model);
	
	auto entityFactoryPlayer = builder->registerEntity(std::move(playerDef));
	entityManager->addEntityFactory("player", entityFactoryPlayer);
}