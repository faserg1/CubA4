#include "CubA4Main.hpp"
#include "AppInfo.hpp"

#include <SDL.h>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "../render/RenderLoader.hpp"
#include "../window/Window.hpp"
#include <engine/IRenderEngine.hpp>

#include <Core.hpp>
#include <config/ICoreConfig.hpp>
#include <config/IFilePaths.hpp>

#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>

#include <loader/ModLoader.hpp>

#include <system/IStartup.hpp>


//TODO: [OOKAMI] Загловки для теста
#include <engine/IRenderManager.hpp>
#include <engine/world/IWorldManager.hpp>
#include <ctime>
#include <cmath>

using namespace CubA4::app;
using namespace CubA4::core::logging;

AppMain::AppMain(int argc, const char *const argv[]) :
	core_(CubA4::core::Core::create(argc, argv)),
	info_(std::make_shared<AppInfo>()), running_(true)
{
	log_ = core_->getLogger()->createTaggedLog(LogSourceSystem::App, "MAIN");
	log_->log(LogLevel::Info, "CubA4 Loader created.");
	renderLoader_ = std::make_shared<CubA4::render::RenderLoader>(core_->getPaths()->renderPath());
	modLoader_ = std::make_shared<CubA4::mod::ModLoader>(core_, info_);
}

AppMain::~AppMain()
{
	shutdown();
	if (log_)
		log_->log(LogLevel::Info, "CubA4 Loader destroyed.");
}

int AppMain::exec()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		auto errMsg = std::string("Unable to initialize SDL.");
		auto details = std::string(SDL_GetError());
		log_->log(LogLevel::Critical, errMsg + " " + details);
		log_->flush();
		return 1;
	}
	try
	{
		if (!setup())
		{
			log_->log(LogLevel::Critical, "Не удалось инициализировать CubA4Loader!");
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
	log_->log(LogLevel::Info, "CubA4 Loader start.");
	loop();
	log_->log(LogLevel::Info, "CubA4 Loader stopped.");
	///////////////////////////
	return 0;
}

std::shared_ptr<CubA4::mod::IModLoader> AppMain::getModLoader() const
{
	return modLoader_;
}

std::shared_ptr<CubA4::render::engine::IRenderManager> AppMain::getRenderManager() const
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	return renderEngine->getRenderManager();
}

const CubA4::render::IRenderInfo &AppMain::getRenderInfo() const
{
	return *renderLoader_->getCurrentRenderInfo();
}

void AppMain::run()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->run();
	core_->getStartup()->run();

	//TODO: [OOKAMI] Убрать тестовые вещи
	auto rm = getRenderManager();
	auto wm = rm->getWorldManager();
	wm->setFieldOfView(60);
	//wm->setCameraPosition({-2,0,0}, 0, 10, 0);
}

void AppMain::stop()
{
	core_->getStartup()->stop();
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->stop();
}

bool AppMain::setup()
{	
	// перед созданием окна, нужно спросить у renderInfo флаги для его создания
	loadRender();
	if (!createWindow())
		return false;
	core_->getStartup()->load(*this);
	initRender();
	core_->getStartup()->setup();
	if (!setupGame())
		return false;
	run();
	return true;
}

void AppMain::shutdown()
{
	log_->flush();
	stop();
	shutdownGame();
	core_->getStartup()->shutdown();
	destroyRender();
	core_->getStartup()->unload();
	unloadRender();
	SDL_Quit();
}

bool AppMain::setupGame()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->setGame(core_->getStartup()->getGame());
	return true;
}

void AppMain::shutdownGame()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->setGame({});
}

void AppMain::doSomeTestThings()
{
	constexpr const float max = 30;
	static float l = -max;
	const float speed = 0.01f;
	static bool up = true;
	if (up)
		l += speed;
	else
		l -= speed;
	if (l > max)
		up = false;
	else if (l < -max)
		up = true;
	auto rm = getRenderManager();
	auto wm = rm->getWorldManager();
	double cl = clock();
	//wm->setCameraRotation(0, 0, cl / CLOCKS_PER_SEC);
	double x = sin(cl / CLOCKS_PER_SEC) * 50;
	double z = cos(cl / CLOCKS_PER_SEC) * 50;
	wm->setCameraPosition({0, 0, 0}, static_cast<float>(x), l, static_cast<float>(z));
}

void AppMain::loop()
{
	SDL_Event event;
	while (running_)
	{
		doSomeTestThings();
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running_ = false;
				break;
				//TODO: [OOKAMI] Ничто так не вечно, как временное... Надеюсь, потом уберу
			case SDL_KEYUP:
				if (event.key.keysym.scancode == SDL_SCANCODE_F11)
					window_->toggleFullscreen();
				break;
			}
		}
		//std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}



void AppMain::loadRender()
{
	auto config = core_->getConfig();
	auto renderInfos = renderLoader_->getRenderInfoCollection();
	if (!renderInfos.size())
		throw std::runtime_error("No render engines!");
	CubA4::render::IRenderInfo *choosedRenderInfo = nullptr;
	CubA4::render::IRenderInfo *finalRenderInfo = nullptr;
	for (auto renderInfo : renderInfos)
	{
		auto name = renderInfo->getRenderEngineId();
		if (name == config->getRenderEngineId())
		{
			choosedRenderInfo = renderInfo;
			renderLoader_->setCurrentRenderInfo(renderInfo);
			finalRenderInfo = choosedRenderInfo;
			break;
		}
	}
	if (!choosedRenderInfo)
	{
		auto *renderInfo = renderInfos[0];
		finalRenderInfo = renderInfo;
		config->setRenderEngineId(renderInfo->getRenderEngineId());
		renderLoader_->setCurrentRenderInfo(renderInfo);
	}
	if (!finalRenderInfo)
		throw std::runtime_error("Cannot find render library!");
	log_->log(LogLevel::Info, std::string("Loading render engine: ") + finalRenderInfo->getRenderEngineId());
	finalRenderInfo->init(info_, core_);
	log_->log(LogLevel::Info, "Render engine loaded");
}

void AppMain::unloadRender()
{
	// TODO: [OOKAMI] unload render library
}

bool AppMain::createWindow()
{
	auto *renderInfo = renderLoader_->getCurrentRenderInfo();
	if (!renderInfo)
	{
		core_->getLogger()->log(LogSourceSystem::App, "MAIN", LogLevel::Critical, "Rener info is not initialized!");
		return false;
	}
	try
	{
		window_ = CubA4::window::Window::createWindow(1024, 720, renderInfo->getSDLWindowFlags());
	}
	catch (std::exception &ex)
	{
		using namespace CubA4::core::logging;
		core_->getLogger()->log(LogSourceSystem::App, "MAIN", LogLevel::Critical, ex.what());
		return false;
	}
	return true;
}

void AppMain::initRender()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->init(window_);
	//Send fucking surface to render info and create fucking render engine
}

void AppMain::destroyRender()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->destroy();
}

