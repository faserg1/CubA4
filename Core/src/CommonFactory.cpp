#include "../include/CommonFactory.hpp"
#include <Core.hpp>
#include <system/Startup.hpp>

std::shared_ptr<CubA4::ICore> CubA4::CommonFactory::createCore(int argc, const char * const argv[], ApplicationFlags flags)
{
	return std::make_shared<CubA4::Core>(argc, argv, flags);
}

std::shared_ptr<CubA4::system::IStartup> CubA4::CommonFactory::createStartup(std::weak_ptr<CubA4::ICore> iCore)
{
	auto core = std::dynamic_pointer_cast<CubA4::Core>(iCore.lock());
	return std::make_shared<CubA4::system::Startup>(core);
}

