#include "./WorldSetup.hpp"
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <ICore.hpp>
#include <system/IEnvironmentBuilder.hpp>

#include "../manager/ModManager.hpp"
#include "../manager/ModRenderManager.hpp"
#include "../manager/ModBlockManager.hpp"
#include "../manager/ModItemManager.hpp"

#include "../../include/block/TestBlock.hpp"

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
	builder->registerObject(std::make_shared<TestBlock>(renderManager->getModel("block")));
}