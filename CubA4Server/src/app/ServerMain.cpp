#include <app/ServerMain.hpp>
#include <app/ServerInfo.hpp>
#include <app/ServerStartup.hpp>

#include <stdexcept>
#include <thread>
#include <chrono>


#include <CommonFactory.hpp>
#include <ICore.hpp>
#include <config/ICoreConfig.hpp>
#include <config/IFilePaths.hpp>

#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>

#include <loader/ModLoader.hpp>

#include <core/IStartup.hpp>


using namespace CubA4::app;
using namespace CubA4::logging;

ServerMain::ServerMain(int argc, const char *const argv[]) :
	core_(CubA4::CommonFactory::createCore(argc, argv, 0 | ApplicationFlag::Default)),
	info_(std::make_shared<ServerInfo>()), running_(true)
{
	log_ = core_->getLogger()->createTaggedLog(LogSourceSystem::App, "MAIN");
	log_->log(LogLevel::Info, "CubA4 Server created.");
}

ServerMain::~ServerMain()
{
	shutdown();
	if (log_)
		log_->log(LogLevel::Info, "CubA4 Server destroyed.");
}

int ServerMain::exec()
{
	try
	{
		if (!setup())
		{
			log_->log(LogLevel::Critical, "Не удалось инициализировать CubA4Server!");
			// TODO: [OOKAMI] В ядро положить коды ошибок
			return 1;
		}			
	}
	catch (const std::exception &ex)
	{
		log_->log(LogLevel::Critical, ex.what());
		return 1;
	}
	///////////////////////////
	ServerStartup startup(*this, core_);

	///////////////////////////
	log_->log(LogLevel::Info, "CubA4 Server start.");
	loop(startup);
	log_->log(LogLevel::Info, "CubA4 Server stopped.");
	///////////////////////////
	return 0;
}

std::function<std::shared_ptr<CubA4::mod::IModLoader>()> ServerMain::getModLoaderFactory() const
{
	return [this]() -> std::shared_ptr<CubA4::mod::IModLoader>
	{
		return std::make_shared<CubA4::mod::ModLoader>(core_, info_);
	};
}

std::shared_ptr<const CubA4::info::IApplicationInfo> ServerMain::getApplicationInfo() const
{
	return info_;
}

bool ServerMain::setup()
{
	return true;
}

void ServerMain::shutdown()
{
	log_->flush();
	running_ = false;
}

void ServerMain::loop(ServerStartup &startup)
{
	double time = clock();
	while (running_)
	{
		double now = clock();
		startup.nextMainLoopIteration(now - time);
		time = now;
	}
}
