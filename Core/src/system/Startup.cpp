#include "../../include/system/Startup.hpp"
#include "../../include/system/EnvironmentBuilder.hpp"
#include <system/IAppCallback.hpp>
#include <mod/IModLoader.hpp>
#include <stdexcept>
using namespace CubA4::core::system;
using namespace CubA4::core;

Startup::Startup(std::weak_ptr<const ICore> core) :
	core_(core), appCallback_(nullptr)
{
	
}

Startup::~Startup()
{
	
}

void Startup::setup(system::IAppCallback &appCallback)
{
	appCallback_ = &appCallback;
	modLoader_ = appCallback_->getModLoader();
	initMods();
}

void Startup::run()
{
	if (!appCallback_)
		throw std::runtime_error("Startup not initialized!");
}

void Startup::stop()
{
	unloadMods();
}

void Startup::initMods()
{
	modLoader_->find();
	modLoader_->load();

	auto envBuilder = std::make_shared<EnvironmentBuilder>();
	modLoader_->setup(envBuilder);
}

void Startup::unloadMods()
{
	modLoader_->unload();
}