#include "CubA4Main.hpp"
#include "AppInfo.hpp"
#include "AppStartup.hpp"

#include <controls/ButtonAdapter.hpp>

#include <SDL.h>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "../render/RenderLoader.hpp"
#include "../window/Window.hpp"
#include <engine/IRenderEngine.hpp>

#include <CommonFactory.hpp>
#include <ICore.hpp>
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
using namespace CubA4::logging;
using namespace CubA4::controls;

AppMain::AppMain(int argc, const char *const argv[]) :
	core_(CubA4::CommonFactory::createCore(argc, argv)),
	info_(std::make_shared<AppInfo>()), running_(true)
{
	log_ = core_->getLogger()->createTaggedLog(LogSourceSystem::App, "MAIN");
	log_->log(LogLevel::Info, "CubA4 Loader created.");
	renderLoader_ = std::make_shared<CubA4::render::RenderLoader>(core_->getPaths()->renderPath(), core_->getRuntime());
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
	AppStartup startup(*this, core_, renderLoader_->getCurrentRenderInfo()->getRenderEngine());
	///////////////////////////
	log_->log(LogLevel::Info, "CubA4 Loader start.");
	loop(startup);
	log_->log(LogLevel::Info, "CubA4 Loader stopped.");
	///////////////////////////
	return 0;
}

std::function<std::shared_ptr<CubA4::mod::IModLoader>()> CubA4::app::AppMain::getModLoaderFactory() const
{
	return [this]() -> std::shared_ptr<CubA4::mod::IModLoader>
	{
		return std::make_shared<CubA4::mod::ModLoader>(core_, info_);
	};
}

std::shared_ptr<const CubA4::info::IApplicationInfo> CubA4::app::AppMain::getApplicationInfo() const
{
	return info_;
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

bool AppMain::setup()
{	
	// перед созданием окна, нужно спросить у renderInfo флаги для его создания
	loadRender();
	if (!createWindow())
		return false;
	initRenderEngine();
	return true;
}

void AppMain::shutdown()
{
	log_->flush();
	destroyRenderEngine();
	unloadRender();
	SDL_Quit();
}

void AppMain::loop(AppStartup &startup)
{
	SDL_Event event;
	double time = clock();
	while (running_)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running_ = false;
				break;
			case SDL_MOUSEMOTION:
				{
					const auto rel = SDL_GetRelativeMouseMode();
					startup.mouseMove(rel ? event.motion.xrel : event.motion.x, rel ? event.motion.yrel : event.motion.y, rel);
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				{
					const auto mods = ButtonAdapter::adapt(SDL_GetModState());
					startup.keyChanged(ButtonAdapter::adaptMouse(event.button.button), mods, event.button.state == SDL_PRESSED);
					break;
				}
			case SDL_KEYUP:
				{
					auto btn = ButtonAdapter::adapt(event.key.keysym.scancode);
					auto mods = ButtonAdapter::adapt(event.key.keysym.mod);
					startup.keyChanged(btn, mods, false);
				}
				//TODO: [OOKAMI] Ничто так не вечно, как временное... Надеюсь, потом уберу
				if (event.key.keysym.scancode == SDL_SCANCODE_F11)
					window_->toggleFullscreen();
				break;
			case SDL_KEYDOWN:
				{
					auto btn = ButtonAdapter::adapt(event.key.keysym.scancode);
					auto mods = ButtonAdapter::adapt(event.key.keysym.mod);
					startup.keyChanged(btn, mods, true);
					break;
				}
			case SDL_WINDOWEVENT:
				{
					switch (event.window.event)
					{
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						{
							auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
							renderEngine->onWindowResized();
							break;
						}
					default:
						break;
					}
					
					break;
				}
			}
		}
		double now = clock();
		startup.nextMainLoopIteration(now - time);
		time = now;
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
		auto config = renderInfo->getRenderConfig();
		auto [width, height] = config->getRenderResolution();
		
		if (!width || !height)
		{
			width = 1280;
			height = 720;
			config->setRenderResolution({width, height});
		}
		
		window_ = CubA4::window::Window::createWindow(width, height, renderInfo->getSDLWindowFlags());
	}
	catch (std::exception &ex)
	{
		using namespace CubA4::logging;
		core_->getLogger()->log(LogSourceSystem::App, "MAIN", LogLevel::Critical, ex.what());
		return false;
	}
	return true;
}

void AppMain::initRenderEngine()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->init(window_);
}

void AppMain::destroyRenderEngine()
{
	auto renderEngine = renderLoader_->getCurrentRenderInfo()->getRenderEngine();
	renderEngine->destroy();
}

std::pair<bool, CubA4::game::controller::BMods> AppMain::getButtonState(CubA4::game::controller::Button btn) const
{
	const auto *keys = SDL_GetKeyboardState(nullptr);
	const auto mods = SDL_GetModState();
	const auto idx = ButtonAdapter::adapt(btn);
	return std::make_pair(idx != SDL_SCANCODE_UNKNOWN ? (bool) keys[idx] : false, ButtonAdapter::adapt(mods));
}

bool AppMain::requestMouseCapture(bool enable)
{
	return SDL_SetRelativeMouseMode(static_cast<SDL_bool>(enable)) == 0;
}