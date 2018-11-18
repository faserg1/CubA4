#include "CubA4Main.hpp"
#include "AppInfo.hpp"

#include <SDL.h>
#include <stdexcept>

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

using namespace CubA4::app;
using namespace CubA4::core::logging;

AppMain::AppMain(int argc, const char *const argv[]) :
	core_(CubA4::core::Core::create(argc, argv)),
	info_(std::make_shared<AppInfo>())
{
	log_ = core_->getLogger()->createTaggedLog(LogSourceSystem::App, "MAIN");
	log_->log(LogLevel::Info, "CubA4 Loader start.");
	renderLoader_ = std::make_shared<CubA4::render::RenderLoader>(core_->getPaths()->renderPath());
	modLoader_ = std::make_shared<CubA4::mod::ModLoader>(core_, info_);
}

int AppMain::exec()
{
	SDL_Init(SDL_INIT_VIDEO);
	try
	{
		loadRender();
		if (!createWindow())
			// TODO: [OOKAMI] В ядро положить коды ошибок
			return 1;
		initRender();
		core_->getStartup()->setup(*this);
		run();
	}
	catch (const std::exception ex)
	{
		stop();
		core_->getStartup()->unload();
		destroyRender();
		unloadRender();
		SDL_Quit();
		log_->log(LogLevel::Critical, ex.what());
		return 1;
	}
	///////////////////////////
	loop();
	///////////////////////////
	stop();
	core_->getStartup()->unload();
	destroyRender();
	unloadRender();
	SDL_Quit();
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

void  AppMain::unloadRender()
{
	// TODO: [OOKAMI] unload render library
}

bool AppMain::createWindow()
{
	auto *renderInfo = renderLoader_->getCurrentRenderInfo();
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

void AppMain::run()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->run();
	core_->getStartup()->run();
}

void AppMain::stop()
{
	core_->getStartup()->stop();
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->stop();
}

void AppMain::loop()
{
	SDL_Event event;
	while (running_)
	{
		if (SDL_WaitEvent(&event))
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
	}
}

