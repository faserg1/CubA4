#include "../include/ModVanilla.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
using namespace CubA4::mod;
using namespace CubA4::core;

ModVanilla::ModVanilla()
{
	
}

ModVanilla::~ModVanilla()
{
	
}

void ModVanilla::load(std::shared_ptr<const ICore> core)
{
	core_ = core;
	renderStartup_.load(core);
	worldSetup_.load(core);
}

void ModVanilla::preinit()
{

}

void ModVanilla::link(std::shared_ptr<const IModLinker> linker)
{

}

void ModVanilla::init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder)
{
	renderStartup_.init(builder);
	renderStartup_.init(builder);
}

void ModVanilla::configure()
{

}

void ModVanilla::done()
{
	core_->getLogger()->flush();
}

void ModVanilla::preunload()
{

}