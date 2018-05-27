#include "./VulkanSDLExtension.hpp"
#include "../VulkanSurface.hpp"
#include "../VulkanInstance.hpp"
#include <window/IWindow.hpp>
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
#include <stdexcept>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;
using namespace CubA4::window;

VulkanSDLExtension::VulkanSDLExtension(std::shared_ptr<IWindow> window) :
	window_(window)
{
	
}

VulkanSDLExtension::~VulkanSDLExtension()
{
	
}

std::vector<std::string> VulkanSDLExtension::names() const
{
	unsigned int extCount;
	if (!SDL_Vulkan_GetInstanceExtensions(window_->getSDLWindow(), &extCount, nullptr))
		throw std::runtime_error("Cant get extension count for SDL Window & Vulkan");
	std::vector<const char*> extensions(extCount);
	if (!SDL_Vulkan_GetInstanceExtensions(window_->getSDLWindow(), &extCount, extensions.data()))
		throw std::runtime_error("Cant get extensions for SDL Window & Vulkan");
	return std::vector<std::string>(extensions.begin(), extensions.end());
}

void VulkanSDLExtension::init(std::shared_ptr<const VulkanInstance> instance)
{
	VkSurfaceKHR nativeSurface;
	if (!SDL_Vulkan_CreateSurface(window_->getSDLWindow(), instance->getInstance(), &nativeSurface))
		throw std::runtime_error("Cant create surface!");
	surface_ = std::make_shared<VulkanSurface>(nativeSurface);
}

void VulkanSDLExtension::destroy(std::shared_ptr<const VulkanInstance> instance)
{
	vkDestroySurfaceKHR(instance->getInstance(), surface_->getSurface(), nullptr);
	surface_.reset();
}


std::shared_ptr<const VulkanSurface> VulkanSDLExtension::getSurface() const
{
	return surface_;
}