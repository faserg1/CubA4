#include "../../include/system/Startup.hpp"
#include "../../include/system/EnvironmentBuilderData.hpp"
#include "../../include/system/EnvironmentBuilder.hpp"
#include "../../include/system/EnvironmentContext.hpp"
#include "../../include/system/Environment.hpp"
#include "../../include/game/Game.hpp"
#include <system/IAppCallback.hpp>
#include <mod/IModLoader.hpp>
#include <stdexcept>
using namespace CubA4::core::system;
using namespace CubA4::core;

Startup::Startup(std::weak_ptr<const ICore> core) :
	core_(core), appCallback_(nullptr)
{
	
}

Startup::~Startup()
{
	
}

void Startup::setup(system::IAppCallback &appCallback)
{
	appCallback_ = &appCallback;
	modLoader_ = appCallback_->getModLoader();
	initGame();
	initMods();
}

void Startup::unload()
{
	unloadMods();
}

void Startup::run()
{
	if (!appCallback_)
		throw std::runtime_error("Startup not initialized!");
	game_->run();
}

void Startup::stop()
{
	game_->stop();
	destroyGame();
}

void Startup::initMods()
{
	modLoader_->find();
	modLoader_->load();

	EnvironmentBuilderData envBuilderData(appCallback_->getRenderManager(), appCallback_->getRenderInfo());
	modLoader_->setup([&envBuilderData](const CubA4::mod::IModInfo &modInfo) -> std::shared_ptr<CubA4::core::system::IEnvironmentBuilder>
	{
		auto envBuilderContext = EnvironmentBuilderContext(modInfo);
		return std::make_shared<EnvironmentBuilder>(envBuilderData, envBuilderContext);
	});

	EnvironmentContext envContext(std::move(envBuilderData.getIdentityMap()), std::move(envBuilderData.getObjects()));
	auto env = std::make_shared<Environment>(std::move(envContext));
	game_->setupEnvironment(env);
}

void Startup::unloadMods()
{
	if (!modLoader_)
		return;
	modLoader_->unload();
}

void Startup::initGame()
{
	game_ = std::make_shared<CubA4::core::game::Game>();
}

void Startup::destroyGame()
{
	game_.reset();
}