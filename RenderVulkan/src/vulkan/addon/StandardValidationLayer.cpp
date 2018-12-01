#include "./StandardValidationLayer.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

StandardValidationLayer::StandardValidationLayer()
{
	
}

StandardValidationLayer::~StandardValidationLayer()
{
	
}

std::vector<std::string> StandardValidationLayer::names() const
{
	std::vector<std::string> metaName = {
		"VK_LAYER_LUNARG_standard_validation"
	};
	std::vector<std::string> nativeNames = {
		"VK_LAYER_GOOGLE_threading",
		"VK_LAYER_LUNARG_parameter_validation",
		"VK_LAYER_LUNARG_device_limits",
		"VK_LAYER_LUNARG_object_tracker",
		"VK_LAYER_LUNARG_image",
		"VK_LAYER_LUNARG_core_validation",
		"VK_LAYER_LUNARG_swapchain",
		"VK_LAYER_GOOGLE_unique_objects",
	};
	if (checkNames(metaName))
		return std::move(metaName);
	return std::move(nativeNames);
}

void StandardValidationLayer::init(std::shared_ptr<const Instance> instance)
{
}

void StandardValidationLayer::destroy(std::shared_ptr<const Instance> instance)
{
}

void StandardValidationLayer::added(InstanceBuilder &builder)
{

}
