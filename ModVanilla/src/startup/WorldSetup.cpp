#include "./WorldSetup.hpp"
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <ICore.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <resources/IResourcesManager.hpp>
#include <world/TestWorldDefinition.hpp>

using namespace CubA4::startup;
using namespace CubA4::manager;
using namespace CubA4::system;
using namespace CubA4::logging;

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
	log_->log(LogLevel::Info, "Initialisating world");
	auto blockManager = manager_->getBlockManager();
	auto block = blockManager->getBlock("test1");
	builder->registerObject(block);
	testWorld_ = builder->createWorld(std::make_shared<CubA4::world::TestWorldDefinition>());
}

void WorldSetup::done()
{
	// Testing rendering. later delete this ugly shit!
	auto blockManager = manager_->getBlockManager();
	auto block1 = blockManager->getBlock("test1");
	auto block2 = blockManager->getBlock("test2");
	auto modWorld = std::const_pointer_cast<CubA4::world::IWorld>(testWorld_);
	modWorld->test({block1, block2});
}