#include "Core.hpp"
#include "config/CoreConfig.hpp"
#include "config/FilePaths.hpp"
#include "logging/Logger.hpp"
#include "system/Startup.hpp"
#include "resources/ResourcesManager.hpp"
#include "cache/CacheManager.hpp"
#include "system/Runtime.hpp"
#include <stdexcept>
#include <boost/stacktrace.hpp>
#include <sstream>

using namespace CubA4::core;
using namespace CubA4::core::system;

Core::Core(int argc, const char *const argv[]) :
	paths_(std::make_shared<config::FilePaths>(argc, argv))
{
	runtime_ = std::make_shared<system::Runtime>();
	config_ = std::make_shared<config::CoreConfig>(paths_->configPath());
	logger_ = logging::Logger::create(paths_->logsPath());
	resourceManager_ = std::make_shared<resources::ResourcesManager>(paths_->resourcesPath());
	cacheManager_= std::make_shared<cache::CacheManager>(paths_->cachePath());
}

Core::~Core()
{

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

std::shared_ptr<resources::IResourcesManager> Core::getResourcesManager() const
{
	return resourceManager_;
}

std::shared_ptr<cache::ICacheManager> Core::getCacheManager() const
{
	return cacheManager_;
}

std::shared_ptr<system::IRuntime> Core::getRuntime()
{
	return runtime_;
}

void Core::criticalException() const
{
	logger_->flush();
	auto print = [this](const std::string &msg)
	{
		logger_->log(CubA4::core::logging::LogSourceSystem::Core, "TERMINATE", CubA4::core::logging::LogLevel::Critical, msg);
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