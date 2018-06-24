#include "./VulkanDeviceExtension.hpp"
#include "../VulkanPhysicalDevice.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanDeviceExtensionData
				{
					std::vector<VkExtensionProperties> extensions;
				};
			}
		}
	}
}

VulkanDeviceExtension::VulkanDeviceExtension(std::weak_ptr<VulkanPhysicalDevice> physicalDevice) :
	VulkanDeviceAddon(physicalDevice), data_(std::make_shared<VulkanDeviceExtensionData>())
{
	if (auto pd = physicalDevice_.lock())
	{
		uint32_t extCount = 0;
		if (vkEnumerateDeviceExtensionProperties(pd->getPhysicalDevice(), nullptr, &extCount, nullptr) != VK_SUCCESS)
			throw std::runtime_error("Unable to enumerate device extensions.");
		data_->extensions.resize(extCount);
		if (vkEnumerateDeviceExtensionProperties(pd->getPhysicalDevice(), nullptr, &extCount, data_->extensions.data()) != VK_SUCCESS)
			throw std::runtime_error("Unable to enumerate device extensions.");
	}
	else
		throw std::runtime_error("Unable to get physical device");
}

VulkanDeviceExtension::~VulkanDeviceExtension()
{
	
}

std::vector<std::string> VulkanDeviceExtension::allNames() const
{
	std::vector<std::string> all;
	all.reserve(data_->extensions.size());
	for (VkExtensionProperties &extProp : data_->extensions)
		all.push_back(extProp.extensionName);
	return all;
}