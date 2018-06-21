#include "./SDLExtension.hpp" 
#include "../Surface.hpp" 
#include "../Instance.hpp" 
#include <window/IWindow.hpp>
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
#include <stdexcept>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;
using namespace CubA4::window;

SDLExtension::SDLExtension(std::shared_ptr<IWindow> window) :
	window_(window)
{
	
}

SDLExtension::~SDLExtension()
{
	
}

std::vector<std::string> SDLExtension::names() const
{
	unsigned int extCount;
	if (!SDL_Vulkan_GetInstanceExtensions(window_->getSDLWindow(), &extCount, nullptr))
		throw std::runtime_error("Cant get extension count for SDL Window & Vulkan");
	std::vector<const char*> extensions(extCount);
	if (!SDL_Vulkan_GetInstanceExtensions(window_->getSDLWindow(), &extCount, extensions.data()))
		throw std::runtime_error("Cant get extensions for SDL Window & Vulkan");
	return std::vector<std::string>(extensions.begin(), extensions.end());
}

void SDLExtension::init(std::shared_ptr<const Instance> instance)
{
	VkSurfaceKHR nativeSurface;
	if (!SDL_Vulkan_CreateSurface(window_->getSDLWindow(), instance->getInstance(), &nativeSurface))
		throw std::runtime_error("Cant create surface!");
	surface_ = std::make_shared<Surface>(nativeSurface);
}

void SDLExtension::destroy(std::shared_ptr<const Instance> instance)
{
	vkDestroySurfaceKHR(instance->getInstance(), surface_->getSurface(), nullptr);
	surface_.reset();
}

void SDLExtension::added(InstanceBuilder &builder)
{

}

std::shared_ptr<const Surface> SDLExtension::getSurface() const
{
	return surface_;
}