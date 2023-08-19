#include "./WorldSetup.hpp"
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <ICore.hpp>
#include <core/IEnvironmentBuilder.hpp>
#include <resources/IResourcesManager.hpp>
#include <world/TestWorldDefinition.hpp>

using namespace CubA4::startup;
using namespace CubA4::manager;
using namespace CubA4::core;
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
	testWorld_ = builder->createWorld(std::make_shared<CubA4::world::TestWorldDefinition>(*core_, *manager_->getBlockManager()));
	testDimension_ = testWorld_->getDimensions().front();
}

void WorldSetup::done()
{
	auto env = core_->getEnvironment();
	testWorldId_ = env->getId(testWorld_);
	testDimensionId_ = env->getId(testDimension_);
}

WorldSetup::IdType WorldSetup::getTestWorldId() const
{
	return testWorldId_;
}

WorldSetup::IdType WorldSetup::getTestDimensionId() const
{
	return testDimensionId_;
}