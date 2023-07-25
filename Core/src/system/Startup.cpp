#include "Startup.hpp"
#include "EnvironmentBuilderData.hpp"
#include "EnvironmentBuilder.hpp"
#include "EnvironmentContext.hpp"
#include "Environment.hpp"
#include <game/Game.hpp>
#include <system/IAppCallback.hpp>
#include <mod/IModLoader.hpp>
#include <stdexcept>
using namespace CubA4::system;

Startup::Startup(std::shared_ptr<Core> core) :
	core_(core), appCallback_(nullptr)
{
	
}

Startup::~Startup()
{
	unloadMods();
}

void Startup::load(system::IAppCallback &appCallback)
{
	appCallback_ = &appCallback;
	auto modLoaderFactory = appCallback.getModLoaderFactory();
	modLoader_ = modLoaderFactory();
	modLoader_->find();
	modLoader_->load();
}

void Startup::setup()
{	
	initGame();
	loadConfigs();
	initMods();
}

void Startup::shutdown()
{
	modLoader_->shutdown();
}

void Startup::run()
{
	startMods();
	if (!appCallback_)
		throw std::runtime_error("Startup not initialized!");
	game_->run();
}

void Startup::stop()
{
	stopMods();
	if (game_)
		game_->stop();
	saveConfigs();
	destroyGame();
}

std::shared_ptr<CubA4::game::IGame> Startup::getGame() const
{
	return game_;
}

void Startup::loadConfigs()
{
	if (auto core = core_.lock())
	{
		auto resourceManager = core->getResourcesManager();
		auto bindings = resourceManager->find("config/bindings.json");
		if (bindings)
			game_->getController()->getBindings()->load(bindings);
	}
}

void Startup::saveConfigs()
{
	if (auto core = core_.lock())
	{
		auto resourceManager = core->getResourcesManager();
		auto bindings = resourceManager->edit("config/bindings.json");
		game_->getController()->getBindings()->save(bindings);
	}
}

void Startup::initMods()
{
	EnvironmentBuilderData envBuilderData(appCallback_->getRenderManager(), appCallback_->getRenderInfo(), game_->getController()->getRootActions());
	modLoader_->setup([&envBuilderData, core = core_.lock()](const CubA4::mod::IModInfo &modInfo) -> std::shared_ptr<CubA4::system::IEnvironmentBuilder>
	{
		auto envBuilderContext = EnvironmentBuilderContext(modInfo);
		return std::make_shared<EnvironmentBuilder>(*core, envBuilderData, envBuilderContext);
	});

	EnvironmentContext envContext(std::move(envBuilderData.getIdentityMap()), std::move(envBuilderData.getObjects()));
	auto env = std::make_shared<Environment>(std::move(envContext));
	
	game_->setupEnvironment(env);
	if (auto core = core_.lock())
	{
		core->setEnvironment(env);
	}
	modLoader_->finished();
}

void Startup::unloadMods()
{
	if (auto core = core_.lock())
	{
		core->setEnvironment({});
	}
	if (!modLoader_)
		return;
	modLoader_->unload();
}

void Startup::initGame()
{
	game_ = std::make_shared<CubA4::game::Game>(*appCallback_);
	if (auto core = core_.lock())
	{
		core->setGame(game_);
	}
}

void Startup::destroyGame()
{
	if (auto core = core_.lock())
	{
		core->setGame({});
	}
	game_.reset();
}

void Startup::startMods()
{
	gameControl_ = std::make_unique<CubA4::game::GameControl>(*core_.lock(), *game_);
	modLoader_->start(*gameControl_.get());
}

void Startup::stopMods()
{
	modLoader_->stop();
	gameControl_.reset();
}