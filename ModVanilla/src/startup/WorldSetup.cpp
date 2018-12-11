#include "./WorldSetup.hpp"
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <ICore.hpp>
#include <system/IEnvironmentBuilder.hpp>

#include <world/IWorld.hpp>

#include "../manager/ModManager.hpp"
#include "../manager/ModRenderManager.hpp"
#include "../manager/ModBlockManager.hpp"
#include "../manager/ModItemManager.hpp"

#include "../../include/block/TestBlock.hpp"

#include "../world/TestWorld.hpp"

using namespace CubA4::mod::startup;
using namespace CubA4::mod::manager;
using namespace CubA4::core;
using namespace CubA4::core::system;
using namespace CubA4::core::logging;

using namespace CubA4::mod::block;

WorldSetup::WorldSetup()
{
	
}

WorldSetup::~WorldSetup()
{
	
}

void WorldSetup::load(std::shared_ptr<const ICore> core, std::shared_ptr<ModManager> manager)
{
	manager_ = manager;
	log_ = core->getLogger()->createTaggedLog(LogSourceSystem::Mod, "ModVanilla/WorlSetup");
}

void WorldSetup::init(std::shared_ptr<IEnvironmentBuilder> builder)
{
	log_->log(LogLevel::Info, "Initialisating world");
	auto renderManager = manager_->getModRenderManager();
	auto defaultRenderBlock = renderManager->getModel("block");
	auto defaultRenderMaterial = renderManager->getMaterial("default");
	testBlock_ = std::make_shared<TestBlock>(defaultRenderBlock, defaultRenderMaterial);
	builder->registerObject(testBlock_);
	testWorld_ = builder->createWorld(std::make_shared<CubA4::mod::world::TestWorld>());
}

void WorldSetup::done()
{
	// Testing rendering. later delete the ugly shit!
	auto modWorld = std::const_pointer_cast<CubA4::mod::world::IWorld>(testWorld_);
	modWorld->placeBlocks(testBlock_,
	{
		{0, 0, 0},
		{1, 1, 1}
	});
}