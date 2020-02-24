#include "../include/CommonFactory.hpp"
#include "Core.hpp"
#include "system/Startup.hpp"

using namespace CubA4::core;

std::shared_ptr<ICore> CubA4::core::CommonFactory::createCore(int argc, const char * const argv[])
{
	return std::make_shared<Core>(argc, argv);
}

std::shared_ptr<system::IStartup> CubA4::core::CommonFactory::createStartup(std::weak_ptr<ICore> core)
{
	return std::make_shared<system::Startup>(core);
}

