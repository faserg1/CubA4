#include <SDL.h>
#include "render/RenderLoader.hpp"
#include <Core.hpp>
#include <CoreConfigBase.hpp>
#include <stdexcept>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	CubA4::core::Core core;
	auto config = core.getConfig();

	CubA4::render::RenderLoader renderLoader;
	auto renderInfos = renderLoader.getRenderInfoCollection();
	if (!renderInfos.size())
		throw std::runtime_error("No render engines!");
	CubA4::render::RenderInfo *choosedRenderInfo = nullptr;
	for (auto renderInfo : renderInfos)
	{
		auto name = renderInfo->getRenderEngineId();
		if (name == config->getRenderEngineId())
		{
			choosedRenderInfo = renderInfo;
		}
	}
	if (!choosedRenderInfo)
	{
		auto *renderInfo = renderInfos[0];
		config->setRenderEngineId(renderInfo->getRenderEngineId());
		renderLoader.setCurrentRenderInfo(renderInfo);
	}
	SDL_Quit();
	return 0;
}