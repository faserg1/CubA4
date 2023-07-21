#include "ModVanilla.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <ModVanillaConst.hpp>
#include <fmt/format.h>
using namespace CubA4::mod;

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
	blockSetup_.load(core, manager_);
	worldSetup_.load(core, manager_);
}

void ModVanilla::preinit(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder)
{
	renderStartup_.preinit(builder);
}

void ModVanilla::link(std::shared_ptr<const IModLinker> linker)
{

}

void ModVanilla::init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder)
{
	blockSetup_.init(builder);
	worldSetup_.init(builder);
}

void ModVanilla::configure(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder)
{

}

void ModVanilla::prefinish(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder)
{
	core_->getLogger()->flush();
}

void ModVanilla::finish()
{
	worldSetup_.done();
	core_->getLogger()->flush();
}

void ModVanilla::start(CubA4::game::IGameControl &gameControl)
{
	gameControl_ = &gameControl;

	auto worldName = std::format("@{}#{}", ModVanillaId, "testWorld");
	auto dimName = std::format("@{}#{}", ModVanillaId, "testDimension");
	gameControl_->requestWorldChange(worldName, dimName);
}

void ModVanilla::stop()
{
	gameControl_ = nullptr;
}

void ModVanilla::preunload()
{
	manager_.reset();
}

const IModInfo &ModVanilla::getInfo() const
{
	return modInfo_;
}

std::weak_ptr<const CubA4::manager::IModManager> ModVanilla::getManager() const
{
	return manager_;
}