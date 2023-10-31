#include <startup/EntitySetup.hpp>
#include <entities/PlayerDefinition.hpp>
#include <entities/CubeEntityDefinition.hpp>
#include <physics/PlayerPhysicsDefinition.hpp>
#include <physics/CubeEntityPhysicsDefinition.hpp>
#include <ICore.hpp>
#include <physics/IPhysicsManager.hpp>
#include <physics/IPhysicsFactory.hpp>

using namespace CubA4::startup;
using namespace CubA4::logging;
using namespace CubA4::resources;
using namespace CubA4::manager;

EntitySetup::EntitySetup(std::shared_ptr<const CubA4::mod::ModControl> modControl) :
	modControl_(modControl)
{
	if (!modControl)
		throw std::runtime_error("WTF?!!");
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
	auto &physicsFactory = core_->getPhysicsManager()->getPhysicsFactory();

	auto model = renderManager->getModel("test-cube-player");

	auto physBody = physicsFactory.createBoxCollisionBody({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5});
	auto playerPhysDef = std::make_shared<CubA4::physics::PlayerPhysicsDefinition>(physBody);
	auto cubePhysDef = std::make_shared<CubA4::physics::CubeEntityPhysicsDefinition>(physBody);

	auto playerDef = std::make_unique<object::PlayerDefinition>(core_, model, playerPhysDef, modControl_);
	auto cubeDef = std::make_unique<object::CubeEntityDefinition>(core_, model, cubePhysDef);
	
	auto entityFactoryPlayer = builder->registerEntity(std::move(playerDef));
	auto entityFactoryCube = builder->registerEntity(std::move(cubeDef));
	entityManager->addEntityFactory("player", entityFactoryPlayer);
	entityManager->addEntityFactory("cube", entityFactoryCube);
}