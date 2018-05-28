#include "./VulkanInstanceExtension.hpp"
#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
using namespace CubA4::render::vulkan::addon;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanExtensionPrivate
				{
					std::vector<VkExtensionProperties> extensions;
				};
			}
		}
	}
}

VulkanExtension::VulkanExtension() :
	data_(std::make_shared<VulkanExtensionPrivate>())
{
	uint32_t extCount = 0;
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance extensions.");
	data_->extensions.resize(extCount);
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, data_->extensions.data()) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance extensions.");
}

std::vector<std::string> VulkanExtension::allNames() const
{
	std::vector<std::string> all;
	all.reserve(data_->extensions.size());
	for (VkExtensionProperties &extProp : data_->extensions)
		all.push_back(extProp.extensionName);
	return all;
}

VulkanExtension::~VulkanExtension()
{
	
}
