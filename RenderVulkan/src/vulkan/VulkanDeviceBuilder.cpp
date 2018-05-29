#include "./VulkanDeviceBuilder.hpp"
#include "./VulkanDevice.hpp"
#include "./VulkanInstance.hpp"
#include "./VulkanSurface.hpp"
#include "addon/VulkanDeviceExtension.hpp"
#include "addon/VulkanDeviceLayer.hpp"
#include <vector>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include <cstdint>
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
				VkPhysicalDevice choosedDevice;
				uint32_t renderQueueIndex;
				uint32_t presentQueueIndex;
			};
		}
	}
}

VulkanDeviceBuilder::VulkanDeviceBuilder(std::shared_ptr<const VulkanInstance> instance,
	std::weak_ptr<const VulkanSurface> surface) :
	data_(std::make_shared<VulkanDeviceBuilderData>()), instance_(instance), surface_(surface)
{
	enumPhysicalDevices();
	choosePhysicalDevice();
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
	vkDestroyDevice(device->getDevice(), nullptr);
}

void VulkanDeviceBuilder::enumPhysicalDevices()
{
	uint32_t physicalDevicesCount;
	if (vkEnumeratePhysicalDevices(instance_->getInstance(), &physicalDevicesCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Cannot list physical devices");
	data_->physicalDevices.resize(physicalDevicesCount);
	if (vkEnumeratePhysicalDevices(instance_->getInstance(), &physicalDevicesCount, data_->physicalDevices.data()) != VK_SUCCESS)
		throw std::runtime_error("Cannot list physical devices");
}

void VulkanDeviceBuilder::choosePhysicalDevice()
{
	for (auto physicalDevice : data_->physicalDevices)
	{
		uint32_t queueCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueFamilyProperties.data());
		
		uint32_t renderIndex = UINT32_MAX;
		uint32_t presentIndex = UINT32_MAX;

		for (uint32_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyProperties.size(); queueFamilyIndex++)
		{
			if (presentIndex == UINT32_MAX)
			{
				if (auto surface = surface_.lock())
				{
					VkBool32 supported;
					if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface->getSurface(), &supported) == VK_SUCCESS)
					{
						if (supported)
							presentIndex = queueFamilyIndex;
					}
				}
				else
					throw std::runtime_error("Surface gone...");
			}

			if (renderIndex == UINT32_MAX)
			{
				auto props = queueFamilyProperties[queueFamilyIndex];
				if (props.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT))
					renderIndex = queueFamilyIndex;
			}
		}
		
		if (renderIndex == UINT32_MAX || presentIndex == UINT32_MAX)
			continue;

		data_->choosedDevice = physicalDevice;
		data_->renderQueueIndex = renderIndex;
		data_->presentQueueIndex = presentIndex;
		break;
	}
}
