#include "../include/CommonFactory.hpp"
#include <Core.hpp>
#include <system/Startup.hpp>

std::shared_ptr<CubA4::ICore> CubA4::CommonFactory::createCore(int argc, const char * const argv[])
{
	return std::make_shared<CubA4::Core>(argc, argv);
}

std::shared_ptr<CubA4::system::IStartup> CubA4::CommonFactory::createStartup(std::weak_ptr<CubA4::ICore> core)
{
	return std::make_shared<CubA4::system::Startup>(core);
}

