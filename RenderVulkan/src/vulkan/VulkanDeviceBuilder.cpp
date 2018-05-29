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
#include <algorithm>
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
				uint32_t queueIndex;
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
	if (!layer.available())
		throw std::runtime_error("Extension is not available");
	auto names = layer.names();
	layers_.insert(layers_.end(), names.begin(), names.end());
	layer.added(*this);
}

void VulkanDeviceBuilder::addExtension(addon::VulkanDeviceExtension &extension)
{
	if (!extension.available())
		throw std::runtime_error("Extension is not available");
	auto names = extension.names();
	extensions_.insert(extensions_.end(), names.begin(), names.end());
	extension.added(*this);
}

std::shared_ptr<const VulkanDevice> VulkanDeviceBuilder::build()
{
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	std::vector<const char *> cStrExtensions(extensions_.size());
	std::vector<const char *> cStrLayers(layers_.size());
	std::transform(extensions_.begin(), extensions_.end(), cStrExtensions.begin(), [](std::string &str) {return str.c_str(); });
	std::transform(layers_.begin(), layers_.end(), cStrLayers.begin(), [](std::string &str) {return str.c_str(); });

	createInfo.enabledLayerCount = cStrExtensions.size();
	createInfo.ppEnabledLayerNames = cStrExtensions.data();
	createInfo.enabledExtensionCount = cStrExtensions.size();
	createInfo.ppEnabledExtensionNames = cStrExtensions.data();

	VkDeviceQueueCreateInfo qCreateInfo = {};
	qCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	qCreateInfo.queueCount = 1;
	qCreateInfo.queueFamilyIndex = data_->queueIndex;
	
	createInfo.queueCreateInfoCount = 1;
	createInfo.pQueueCreateInfos = &qCreateInfo;

	VkDevice device;
	if (vkCreateDevice(data_->choosedDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		throw std::runtime_error("Cannot create device");

	return std::make_shared<VulkanDevice>(device);
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
		
		uint32_t queueIndex = UINT32_MAX;

		for (uint32_t queueFamilyIndex = 0; queueFamilyIndex < queueFamilyProperties.size(); queueFamilyIndex++)
		{
			if (auto surface = surface_.lock())
			{
				VkBool32 supported;
				if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface->getSurface(), &supported) == VK_SUCCESS)
				{
					if (!supported)
						continue;
				}
			}
			else
				throw std::runtime_error("Surface gone...");

			auto props = queueFamilyProperties[queueFamilyIndex];
			if (!(props.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT)))
				continue;
			queueIndex = queueFamilyIndex;
			break;
		}

		data_->choosedDevice = physicalDevice;
		data_->queueIndex = queueIndex;
		break;
	}
}
