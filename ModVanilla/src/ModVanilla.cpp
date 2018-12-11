#include "ModVanilla.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
using namespace CubA4::mod;
using namespace CubA4::core;

ModVanilla::ModVanilla(const IModInfo &modInfo) :
	modInfo_(modInfo)
{
	
}

ModVanilla::~ModVanilla()
{
	
}

void ModVanilla::load(std::shared_ptr<const ICore> core)
{
	core_ = core;
	manager_ = std::make_shared<manager::ModManager>();
	renderStartup_.load(core, manager_);
	worldSetup_.load(core, manager_);
}

void ModVanilla::preinit(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder)
{
	renderStartup_.preinit(builder);
}

void ModVanilla::link(std::shared_ptr<const IModLinker> linker)
{

}

void ModVanilla::init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder)
{	
	worldSetup_.init(builder);
}

void ModVanilla::configure(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder)
{

}

void ModVanilla::done(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder)
{
	worldSetup_.done();
	core_->getLogger()->flush();
}

void ModVanilla::preunload()
{
	manager_.reset();
}

const IModInfo &ModVanilla::getInfo() const
{
	return modInfo_;
}

std::weak_ptr<const manager::IModManager> ModVanilla::getManager() const
{
	return manager_;
}