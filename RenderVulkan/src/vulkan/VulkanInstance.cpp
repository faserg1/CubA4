#include "./VulkanInstance.hpp"
using namespace CubA4::render::vulkan;

VulkanInstance::VulkanInstance(VkInstance instance) :
	instance_(instance)
{
	
}

VulkanInstance::~VulkanInstance()
{
	
}

VkInstance VulkanInstance::get() const
{
	return instance_;
}