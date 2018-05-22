#include "../include/Core.hpp"
#include "../include/config/CoreConfig.hpp"
#include "../include/config/FilePaths.hpp"
#include "../include/logging/Logger.hpp"

using namespace CubA4::core;

Core::Core(int argc, const char *const argv[]) :
	paths_(std::make_shared<config::FilePaths>(config::FilePaths(argc, argv)))
{
	config_ = std::make_shared<config::CoreConfig>(config::CoreConfig(paths_->configPath()));
	logger_ = logging::Logger::create(paths_->logsPath());
}

Core::~Core()
{

}

const std::shared_ptr<const config::IFilePaths> Core::getPaths()
{
	return paths_;
}

std::shared_ptr<config::ICoreConfig> Core::getConfig()
{
	return config_;
}

std::shared_ptr<logging::ILogger> CubA4::core::Core::getLogger()
{
	return logger_;
}

