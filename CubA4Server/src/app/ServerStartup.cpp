#include <app/ServerStartup.hpp>
#include <system/IAppCallback.hpp>
#include <system/IStartup.hpp>
#include <CommonFactory.hpp>

#include <ctime>
#include <cmath>
#include <fmt/format.h>

using namespace CubA4::app;

ServerStartup::ServerStartup(CubA4::system::IAppCallback &appCallback, std::weak_ptr<CubA4::ICore> core) :
	appCallback_(appCallback), core_(core),
	startup_(CubA4::CommonFactory::createStartup(core))
{
	startup_->load(appCallback_);
	setup();
}

ServerStartup::~ServerStartup()
{
	shutdown();
}


std::shared_ptr<CubA4::system::IStartup> ServerStartup::getSystemStartup()
{
	return startup_;
}

void ServerStartup::nextMainLoopIteration(double delta)
{
	
}

bool ServerStartup::setup()
{
	startup_->setup();
	if (!setupGame())
		return false;
	run();
	return true;
}

void ServerStartup::shutdown()
{
	stop();
	shutdownGame();
	startup_->shutdown();
}

bool ServerStartup::setupGame()
{
	return true;
}

void ServerStartup::shutdownGame()
{
}

void ServerStartup::run()
{
	startup_->run();
}

void ServerStartup::stop()
{
	startup_->stop();
}
