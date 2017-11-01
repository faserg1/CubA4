#include <SDL.h>
#include "render/RenderLoader.hpp"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	CubA4::render::RenderLoader renderLoader;
	auto renderInfos = renderLoader.getRenderInfoCollection();
	SDL_Quit();
	return 0;
}