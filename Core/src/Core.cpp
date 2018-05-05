#include "../include/Core.hpp"

using namespace CubA4::core;

Core::Core()
{

}

Core::~Core()
{

}

std::shared_ptr<CoreConfigBase> Core::getConfig()
{
	return config_;
}

