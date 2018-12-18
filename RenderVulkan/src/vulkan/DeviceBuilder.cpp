#include "./DeviceBuilder.hpp"
#include "./Device.hpp"
#include "./Instance.hpp"
#include "./Surface.hpp"
#include "./PhysicalDevice.hpp"
#include "addon/DeviceExtension.hpp"
#include "addon/DeviceLayer.hpp"
#include "util/ErrorHelper.hpp"
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
			struct DeviceBuilderData
			{
				std::vector<VkPhysicalDevice> physicalDevices;
				std::shared_ptr<PhysicalDevice> choosedDevice;
				uint32_t queueFamilyIndex;
			};
		}
	}
}

DeviceBuilder::DeviceBuilder(std::shared_ptr<const Instance> instance,
	std::weak_ptr<const Surface> surface) :
	data_(std::make_shared<DeviceBuilderData>()), instance_(instance), surface_(surface)
{
	enumPhysicalDevices();
	choosePhysicalDevice();
}

DeviceBuilder::~DeviceBuilder()
{
	
}

void DeviceBuilder::addLayer(addon::DeviceLayer &layer)
{
	if (!layer.available())
		throw std::runtime_error("Extension is not available");
	auto names = layer.names();
	layers_.insert(layers_.end(), names.begin(), names.end());
	layer.added(*this);
}

void DeviceBuilder::addExtension(addon::DeviceExtension &extension)
{
	if (!extension.available())
		throw std::runtime_error("Extension is not available");
	auto names = extension.names();
	extensions_.insert(extensions_.end(), names.begin(), names.end());
	extension.added(*this);
}

std::weak_ptr<PhysicalDevice> DeviceBuilder::getPhysicalDevice()
{
	return data_->choosedDevice;
}


std::shared_ptr<const Device> DeviceBuilder::build()
{
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	std::vector<const char *> cStrExtensions(extensions_.size());
	std::vector<const char *> cStrLayers(layers_.size());
	std::transform(extensions_.begin(), extensions_.end(), cStrExtensions.begin(), [](std::string &str) {return str.c_str(); });
	std::transform(layers_.begin(), layers_.end(), cStrLayers.begin(), [](std::string &str) {return str.c_str(); });

	createInfo.enabledLayerCount = static_cast<uint32_t>(cStrExtensions.size());
	createInfo.ppEnabledLayerNames = cStrExtensions.data();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(cStrExtensions.size());
	createInfo.ppEnabledExtensionNames = cStrExtensions.data();
	
	VkPhysicalDeviceFeatures availableFeatures = {}, enabledFeatures = {};
	vkGetPhysicalDeviceFeatures(data_->choosedDevice->getPhysicalDevice(), &availableFeatures);

	if (!availableFeatures.shaderInt64)
	{
		throw std::runtime_error("Cannot create device without shaderInt64 feature!");
	}
	enabledFeatures.shaderInt64 = VK_TRUE;
	createInfo.pEnabledFeatures = &enabledFeatures;

	float queuePriorities[2] = { 1.f, 1.f };
	VkDeviceQueueCreateInfo qCreateInfo = {};
	qCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	qCreateInfo.queueCount = 2;
	qCreateInfo.queueFamilyIndex = data_->queueFamilyIndex;
	qCreateInfo.pQueuePriorities = queuePriorities;
	
	createInfo.queueCreateInfoCount = 1;
	createInfo.pQueueCreateInfos = &qCreateInfo;

	VkDevice device;
	if (vkCreateDevice(data_->choosedDevice->getPhysicalDevice(), &createInfo, nullptr, &device) != VK_SUCCESS)
		throw std::runtime_error("Cannot create device");

	VkQueue queue, transmitQueue;
	vkGetDeviceQueue(device, data_->queueFamilyIndex, 0, &queue);
	vkGetDeviceQueue(device, data_->queueFamilyIndex, 1, &transmitQueue);

	return std::make_shared<Device>(device, data_->choosedDevice->getPhysicalDevice(), queue, transmitQueue);
}

void DeviceBuilder::destroy(std::shared_ptr<const Device> device)
{
	if (!device)
		return;
	vkDeviceWaitIdle(device->getDevice());
	vkDestroyDevice(device->getDevice(), nullptr);
}

void DeviceBuilder::enumPhysicalDevices()
{
	uint32_t physicalDevicesCount;
	VkResult result = vkEnumeratePhysicalDevices(instance_->getInstance(), &physicalDevicesCount, nullptr);
	const std::string errMsg = "Cannot list physical devices";
	if (result != VK_SUCCESS)
		throw std::runtime_error(errMsg + " " + util::ErrorHelper::getResultString(result));
	data_->physicalDevices.resize(physicalDevicesCount);
	result = vkEnumeratePhysicalDevices(instance_->getInstance(), &physicalDevicesCount, data_->physicalDevices.data());
	if (result != VK_SUCCESS)
		throw std::runtime_error(errMsg + " " + util::ErrorHelper::getResultString(result));
}

void DeviceBuilder::choosePhysicalDevice()
{
	for (auto physicalDevice : data_->physicalDevices)
	{
		uint32_t queueCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueFamilyProperties.data());
		
		uint32_t queueFamilyIndex = UINT32_MAX;

		for (uint32_t queueFamilyCurrentIndex = 0; queueFamilyCurrentIndex < queueFamilyProperties.size(); queueFamilyCurrentIndex++)
		{
			if (auto surface = surface_.lock())
			{
				VkBool32 supported;
				if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyCurrentIndex, surface->getSurface(), &supported) == VK_SUCCESS)
				{
					if (!supported)
						continue;
				}
			}
			else
				throw std::runtime_error("Surface gone...");

			auto props = queueFamilyProperties[queueFamilyCurrentIndex];
			if (!(props.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT)))
				continue;
			queueFamilyIndex = queueFamilyCurrentIndex;
			break;
		}

		data_->choosedDevice = std::make_shared<PhysicalDevice>(physicalDevice);
		data_->queueFamilyIndex = queueFamilyIndex;
		break;
	}
}
