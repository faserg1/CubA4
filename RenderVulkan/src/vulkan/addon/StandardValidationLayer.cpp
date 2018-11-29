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
	return
	{
		//"VK_LAYER_LUNARG_standard_validation"
		"VK_LAYER_GOOGLE_threading",
		"VK_LAYER_LUNARG_parameter_validation",
		"VK_LAYER_LUNARG_device_limits",
		"VK_LAYER_LUNARG_object_tracker",
		"VK_LAYER_LUNARG_image",
		"VK_LAYER_LUNARG_core_validation",
		"VK_LAYER_LUNARG_swapchain",
		"VK_LAYER_GOOGLE_unique_objects",
	};
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
