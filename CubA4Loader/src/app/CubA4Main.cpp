#include "CubA4Main.hpp"
#include <SDL.h>
#include "../render/RenderLoader.hpp"
#include "../window/Window.hpp"
#include <Core.hpp>
#include <config/ICoreConfig.hpp>
#include <stdexcept>

using namespace CubA4::app;

AppMain::AppMain()
{
	core_ = std::make_shared<CubA4::core::Core>(CubA4::core::Core());
	renderLoader_ = std::make_shared<CubA4::render::RenderLoader>(CubA4::render::RenderLoader());
}

int AppMain::exec()
{
	SDL_Init(SDL_INIT_VIDEO);
	loadRender();
	createWindow();
	loop();
	SDL_Quit();
	return 0;
}

void AppMain::loadRender()
{
	auto config = core_->getConfig();
	auto renderInfos = renderLoader_->getRenderInfoCollection();
	if (!renderInfos.size())
		throw std::runtime_error("No render engines!");
	CubA4::render::IRenderInfo *choosedRenderInfo = nullptr;
	for (auto renderInfo : renderInfos)
	{
		auto name = renderInfo->getRenderEngineId();
		if (name == config->getRenderEngineId())
		{
			choosedRenderInfo = renderInfo;
			renderLoader_->setCurrentRenderInfo(renderInfo);
		}
	}
	if (!choosedRenderInfo)
	{
		auto *renderInfo = renderInfos[0];
		config->setRenderEngineId(renderInfo->getRenderEngineId());
		renderLoader_->setCurrentRenderInfo(renderInfo);
	}
}

void AppMain::createWindow()
{
	auto *renderInfo = renderLoader_->getCurrentRenderInfo();
	window_ = CubA4::window::Window::createWindow(1024, 720, renderInfo->getSDLWindowFlags());
}

void AppMain::initRender()
{
	//Send fucking surface to render info and create fucking render engine
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
			}
		}
	}
}

