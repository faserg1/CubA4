#include "Window.hpp"
#include <SDL_video.h>
using namespace CubA4::window;

Window::Window(int sizeX, int sizeY, int64_t additionalSDLWindowFlags)
{
	window_ = SDL_CreateWindow("CubA4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizeX, sizeY, SDL_WINDOW_SHOWN | additionalSDLWindowFlags);
}

Window::~Window()
{

}

SDL_Window *Window::getSDLWindow()
{
	return window_;
}

std::shared_ptr<Window> Window::createWindow(int sizeX, int sizeY, int64_t additionalSDLWindowFlags)
{
	return std::shared_ptr<Window>(new Window(sizeX, sizeY, additionalSDLWindowFlags), [](Window *cls) {delete cls;});
}