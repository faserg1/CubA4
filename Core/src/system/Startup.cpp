#include "Startup.hpp"
#include "EnvironmentBuilderData.hpp"
#include "EnvironmentBuilder.hpp"
#include "EnvironmentContext.hpp"
#include "Environment.hpp"
#include "../game/Game.hpp"
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

void Startup::load(system::IAppCallback &appCallback)
{
	appCallback_ = &appCallback;
	modLoader_ = appCallback_->getModLoader();
	modLoader_->find();
	modLoader_->load();
}

void Startup::unload()
{
	unloadMods();
}

void Startup::setup()
{	
	initGame();
	initMods();
}

void Startup::shutdown()
{
	modLoader_->shutdown();
}

void Startup::run()
{
	if (!appCallback_)
		throw std::runtime_error("Startup not initialized!");
	game_->run();
}

void Startup::stop()
{
	if (game_)
		game_->stop();
	destroyGame();
}

std::shared_ptr<CubA4::core::game::IGame> Startup::getGame() const
{
	return game_;
}

void Startup::initMods()
{
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