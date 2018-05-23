#include "./VulkanDebugExtension.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

VulkanDebugExtension::VulkanDebugExtension()
{
	
}

VulkanDebugExtension::~VulkanDebugExtension()
{
	
}

std::vector<std::string> VulkanDebugExtension::names() const
{
	return { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
}

void VulkanDebugExtension::init(std::shared_ptr<VulkanInstance> instance)
{

}

void VulkanDebugExtension::destroy(std::shared_ptr<VulkanInstance> instance)
{

}