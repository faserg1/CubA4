#include "../include/Core.hpp"
#include "../include/config/CoreConfig.hpp"
#include "../include/config/FilePaths.hpp"
#include "../include/logging/Logger.hpp"
#include "../include/system/Startup.hpp"
#include <exception>

using namespace CubA4::core;
using namespace CubA4::core::system;

Core::Core(int argc, const char *const argv[]) :
	paths_(std::make_shared<config::FilePaths>(argc, argv))
{
	config_ = std::make_shared<config::CoreConfig>(paths_->configPath());
	logger_ = logging::Logger::create(paths_->logsPath());
}

Core::~Core()
{

}

std::shared_ptr<ICore> Core::create(int argc, const char *const argv[])
{
	auto core = std::shared_ptr<Core>(new Core(argc, argv), [](Core *ptr) {delete ptr; });
	core->core_ = core;
	return core;
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

std::shared_ptr<system::IStartup> Core::getStartup()
{
	if (!startup_)
		startup_ = std::make_shared<system::Startup>(core_);
	return startup_;
}