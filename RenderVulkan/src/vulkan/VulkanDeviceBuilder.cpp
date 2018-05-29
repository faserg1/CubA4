#include "./VulkanDeviceBuilder.hpp"
#include "./VulkanInstance.hpp"
#include "addon/VulkanDeviceExtension.hpp"
#include "addon/VulkanDeviceLayer.hpp"
#include <vector>
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			struct VulkanDeviceBuilderData
			{
				std::vector<VkPhysicalDevice> physicalDevices;
			};
		}
	}
}

VulkanDeviceBuilder::VulkanDeviceBuilder(std::shared_ptr<const VulkanInstance> instance) :
	data_(std::make_shared<VulkanDeviceBuilderData>()), instance_(instance)
{
	enumPhysicalDevices();
}

VulkanDeviceBuilder::~VulkanDeviceBuilder()
{
	
}

void VulkanDeviceBuilder::addLayer(addon::VulkanDeviceLayer &layer)
{
	layer.added(*this);
}

void VulkanDeviceBuilder::addExtension(addon::VulkanDeviceExtension &extension)
{
	extension.added(*this);
}

std::shared_ptr<const VulkanDevice> VulkanDeviceBuilder::build()
{
	return std::shared_ptr<const VulkanDevice>();
}

void VulkanDeviceBuilder::destroy(std::shared_ptr<const VulkanDevice> device)
{
	
}

void VulkanDeviceBuilder::enumPhysicalDevices()
{
	uint32_t physicalDevicesCount;
	vkEnumeratePhysicalDevices(instance_->getInstance(), &physicalDevicesCount, nullptr);
	data_->physicalDevices.resize(physicalDevicesCount);
	vkEnumeratePhysicalDevices(instance_->getInstance(), &physicalDevicesCount, data_->physicalDevices.data());
}

