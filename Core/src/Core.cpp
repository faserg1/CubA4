#include "../include/Core.hpp"
#include "../include/config/CoreConfig.hpp"

using namespace CubA4::core;

Core::Core()
{
	config_ = std::make_shared<config::CoreConfig>(config::CoreConfig());
}

Core::~Core()
{

}

std::shared_ptr<config::ICoreConfig> Core::getConfig()
{
	return config_;
}

std::shared_ptr<const config::IFilePaths> Core::getPaths()
{
	return std::shared_ptr<const config::IFilePaths>();
}

