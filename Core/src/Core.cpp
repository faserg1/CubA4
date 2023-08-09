#include "Core.hpp"
#include "config/CoreConfig.hpp"
#include "config/FilePaths.hpp"
#include "logging/Logger.hpp"
#include <system/Startup.hpp>
#include "model/ModelFactory.hpp"
#include "resources/ResourcesManager.hpp"
#include "resources/FilesystemResourceProvider.hpp"
#include "system/Runtime.hpp"
#include <physics/PhysicsManager.hpp>
#include <object/EntityManager.hpp>
#include <stdexcept>
#include <boost/stacktrace.hpp>
#include <sstream>

using namespace CubA4;
using namespace CubA4::system;

Core::Core(int argc, const char *const argv[], ApplicationFlags flags) :
	appFlags_(flags), paths_(std::make_shared<config::FilePaths>(argc, argv))
{
	runtime_ = std::make_shared<system::Runtime>();
	config_ = std::make_shared<config::CoreConfig>(paths_->configPath());
	logger_ = logging::Logger::create(paths_->logsPath());
	modelFactory_ = std::make_shared<model::ModelFactory>();
	resourceManager_ = std::make_shared<resources::ResourcesManager>();
	entityManager_ = std::make_shared<object::EntityManager>(*this);
	physicsManager_ = std::make_shared<physics::PhysicsManager>(*this);

	auto fsProvider = std::make_shared<resources::FilesystemResourceProvider>(paths_->resourcesPath());
	auto cacheProvider = std::make_shared<resources::FilesystemResourceProvider>(paths_->cachePath());
	auto cfgProvider = std::make_shared<resources::FilesystemResourceProvider>(paths_->configPath());
	resourceManager_->mount(CubA4::resources::ResourcesType::Mod, "data", fsProvider, "data");
	resourceManager_->mount(CubA4::resources::ResourcesType::Cache, "cache", cacheProvider, "cache");
	resourceManager_->mount(CubA4::resources::ResourcesType::Config, "config", cfgProvider, "config");
}

Core::~Core()
{

}

ApplicationFlags Core::getApplicationFlags() const
{
	return appFlags_;
}

ApplicationModeFlags Core::getApplicationModeFlags() const
{
	return appModeFlags_;
}

const std::shared_ptr<const config::IFilePaths> Core::getPaths() const
{
	return paths_;
}

std::shared_ptr<config::ICoreConfig> Core::getConfig() const
{
	return config_;
}

std::shared_ptr<logging::ILogger> Core::getLogger() const
{
	return logger_;
}

std::shared_ptr<model::IModelFactory> Core::getModelFactory() const
{
	return modelFactory_;
}

std::shared_ptr<const resources::IResourcesManager> Core::getResourcesManager() const
{
	return std::const_pointer_cast<const resources::IResourcesManager>(resourceManager_);
}

std::shared_ptr<system::Environment> Core::getEnvironment()
{
	return env_;
}

std::shared_ptr<const system::IEnvironment> Core::getEnvironment() const
{
	return env_;
}

std::shared_ptr<const game::IGame> Core::getGame() const
{
	return game_;
}

std::shared_ptr<system::IRuntime> Core::getRuntime()
{
	return runtime_;
}

std::shared_ptr<object::EntityManager> Core::getEntityManager()
{
	return entityManager_;
}

std::shared_ptr<physics::PhysicsManager> Core::getPhysicsManager()
{
	return physicsManager_;
}

std::shared_ptr<render::engine::IRenderManager> Core::getRenderManager() const
{
	if (!(appFlags_ & ApplicationFlag::Render))
		return {};
	auto appClientCallback = dynamic_cast<IAppClientCallback*>(startup_->getAppCallbacks());
	if (appClientCallback)
		return appClientCallback->getRenderManager();
	return {};
}

const render::IRenderInfo *Core::getRenderInfo() const
{
	if (!(appFlags_ & ApplicationFlag::Render))
		return {};
	auto appClientCallback = dynamic_cast<IAppClientCallback*>(startup_->getAppCallbacks());
	if (appClientCallback)
		return &appClientCallback->getRenderInfo();
	return {};
}

void Core::setApplicationModeFlags(ApplicationModeFlags flags)
{
	appModeFlags_ = flags;
}

void Core::setEnvironment(std::shared_ptr<system::Environment> env)
{
	env_ = env;
}

void Core::setGame(std::shared_ptr<game::IGame> game)
{
	game_ = game;
}

void Core::setStartup(CubA4::system::Startup *startup)
{
	startup_ = startup;
}

void Core::criticalException() const
{
	logger_->flush();
	auto print = [this](const std::string &msg)
	{
		logger_->log(CubA4::logging::LogSourceSystem::Core, "TERMINATE", CubA4::logging::LogLevel::Critical, msg);
	};
	auto st = boost::stacktrace::stacktrace();
	auto frames = st.as_vector();
	print("CubA4 has terminated! Stacktrace:");
	for (auto frame : frames)
	{
		print(frame.name() + " at " + frame.source_file() + ":" + std::to_string(frame.source_line()));
	}
	logger_->flush();
}