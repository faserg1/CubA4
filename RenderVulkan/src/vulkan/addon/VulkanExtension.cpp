#include "./VulkanExtension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
using namespace CubA4::render::vulkan::addon;

VulkanExtension::VulkanExtension()
{
	uint32_t extCount = 0;
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Unaible to enumerate instance extensions.");
	std::vector<VkExtensionProperties> extensions(extCount);
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensions.data()) != VK_SUCCESS)
		throw std::runtime_error("Unaible to enumerate instance extensions.");
}

VulkanExtension::~VulkanExtension()
{
	
}

