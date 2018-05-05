#include "../include/Core.hpp"
#include "../include/CoreConfig.hpp"

using namespace CubA4::core;

Core::Core()
{
	config_ = std::make_shared<CoreConfig>(CoreConfig());
}

Core::~Core()
{

}

std::shared_ptr<CoreConfigBase> Core::getConfig()
{
	return config_;
}

