#include "./WorldSetup.hpp"
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <ICore.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <resources/IResourcesManager.hpp>

#include <world/IWorld.hpp>

#include "../manager/ModManager.hpp"

#include "../../include/block/TestBlock.hpp"

using namespace CubA4::startup;
using namespace CubA4::manager;
using namespace CubA4::system;
using namespace CubA4::logging;

using namespace CubA4::block;

WorldSetup::WorldSetup()
{
	
}

WorldSetup::~WorldSetup()
{
	
}

void WorldSetup::load(std::shared_ptr<const ICore> core, std::shared_ptr<ModManager> manager)
{
	core_ = core;
	manager_ = manager;
	log_ = core->getLogger()->createTaggedLog(LogSourceSystem::Mod, "ModVanilla/WorlSetup");
}

void WorldSetup::init(std::shared_ptr<IEnvironmentBuilder> builder)
{
	/*
	log_->log(LogLevel::Info, "Initialisating world");
	auto renderManager = manager_->getModRenderManager();
	auto defaultRenderBlock = renderManager->getModel("block");
	auto defaultRenderMaterial = renderManager->getMaterial("default");
	auto modelFactory = core_->getModelFactory();
	auto resources = core_->getResourcesManager();
	auto resource = resources->find("data/vanilla/assets/models/test.json");
	auto blockModelDef = modelFactory->createSimpleBlockRenderModelDefinition("block", resource);
	testBlock_ = std::make_shared<TestBlock>(defaultRenderBlock, defaultRenderMaterial, blockModelDef);
	builder->registerObject(testBlock_);
	testWorld_ = builder->createWorld(std::make_shared<CubA4::world::TestWorld>());*/
}

void WorldSetup::done()
{
}