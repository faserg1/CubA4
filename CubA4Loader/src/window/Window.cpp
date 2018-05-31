#include "Window.hpp"
#include <SDL_video.h>
#include <stdexcept>
using namespace CubA4::window;

Window::Window(int sizeX, int sizeY, int64_t additionalSDLWindowFlags)
{
	window_ = SDL_CreateWindow("CubA4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizeX, sizeY, SDL_WINDOW_SHOWN | additionalSDLWindowFlags);
	if (!window_)
		throw std::runtime_error("Window creation failed!");
	fullscreenMode_ = false;
}

Window::~Window()
{

}

SDL_Window *Window::getSDLWindow()
{
	return window_;
}

bool Window::isFullscreen()
{
	return fullscreenMode_;
}

void Window::setFullscreen(bool fullscreen)
{
	fullscreenMode_ = fullscreen;
	SDL_SetWindowFullscreen(window_, (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
}

void Window::toggleFullscreen()
{
	setFullscreen(!isFullscreen());
}

std::shared_ptr<Window> Window::createWindow(int sizeX, int sizeY, int64_t additionalSDLWindowFlags)
{
	return std::shared_ptr<Window>(new Window(sizeX, sizeY, additionalSDLWindowFlags), [](Window *cls) {delete cls;});
}