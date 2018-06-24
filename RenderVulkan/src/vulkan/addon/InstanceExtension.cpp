#include "./InstanceExtension.hpp"
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
				struct InstanceExtensionData
				{
					std::vector<VkExtensionProperties> extensions;
				};
			}
		}
	}
}

InstanceExtension::InstanceExtension() :
	data_(std::make_shared<InstanceExtensionData>())
{
	uint32_t extCount = 0;
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance extensions.");
	data_->extensions.resize(extCount);
	if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, data_->extensions.data()) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance extensions.");
}

std::vector<std::string> InstanceExtension::allNames() const
{
	std::vector<std::string> all;
	all.reserve(data_->extensions.size());
	for (VkExtensionProperties &extProp : data_->extensions)
		all.push_back(extProp.extensionName);
	return all;
}

InstanceExtension::~InstanceExtension()
{
	
}
