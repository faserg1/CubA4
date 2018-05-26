#include "./VulkanStandardValidationLayer.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

VulkanStandardValidationLayer::VulkanStandardValidationLayer()
{
	
}

VulkanStandardValidationLayer::~VulkanStandardValidationLayer()
{
	
}

std::vector<std::string> VulkanStandardValidationLayer::names() const
{
	return {"VK_LAYER_LUNARG_standard_validation"};
}

void VulkanStandardValidationLayer::init(std::shared_ptr<const VulkanInstance> instance)
{
}

void VulkanStandardValidationLayer::destroy(std::shared_ptr<const VulkanInstance> instance)
{
}

