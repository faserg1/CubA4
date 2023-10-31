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
#include <functional>
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
	std::weak_ptr<Surface> surface) :
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

	VkPhysicalDeviceProperties2 deviceProps {};
	deviceProps.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	vkGetPhysicalDeviceProperties2(data_->choosedDevice->getPhysicalDevice(), &deviceProps);

	{
		auto major = VK_VERSION_MAJOR(deviceProps.properties.apiVersion);
		auto minor = VK_VERSION_MINOR(deviceProps.properties.apiVersion);
		auto patch = VK_VERSION_PATCH(deviceProps.properties.apiVersion);
	}
	
	VkPhysicalDeviceFeatures2 availableFeatures = {};
	availableFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;

	VkPhysicalDeviceVulkan11Features available11Features = {};
	VkPhysicalDeviceVulkan12Features available12Features = {};
	VkPhysicalDeviceVulkan13Features available13Features = {};
	
	available11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
	available12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	available13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	
	availableFeatures.pNext = &available11Features;
	available11Features.pNext = &available12Features;
	available12Features.pNext = &available13Features;
	
	vkGetPhysicalDeviceFeatures2(data_->choosedDevice->getPhysicalDevice(), &availableFeatures);

	
	std::vector<VkBool32> requiredFeatures = {
		availableFeatures.features.shaderInt64, // TODO: [OOKAMI] Disable this?
		availableFeatures.features.fillModeNonSolid,
		available13Features.synchronization2
	};
	if (std::any_of(requiredFeatures.begin(), requiredFeatures.end(), std::logical_not{}))
	{
		throw std::runtime_error("Cannot create device without required features!");
	}

	auto enabledFeaturesHolder = std::make_unique<DeviceEnabledFeaturesHolder>();
	enabledFeaturesHolder->enabledFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	enabledFeaturesHolder->enabled11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
	enabledFeaturesHolder->enabled12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	enabledFeaturesHolder->enabled13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;

	enabledFeaturesHolder->enabledFeatures.pNext = &enabledFeaturesHolder->enabled11Features;
	enabledFeaturesHolder->enabled11Features.pNext = &enabledFeaturesHolder->enabled12Features;
	enabledFeaturesHolder->enabled12Features.pNext = &enabledFeaturesHolder->enabled13Features;

	enabledFeaturesHolder->enabledFeatures.features.shaderInt64 = VK_TRUE;
	enabledFeaturesHolder->enabledFeatures.features.fillModeNonSolid = VK_TRUE;

	enabledFeaturesHolder->enabled13Features.synchronization2 = VK_TRUE;

	enabledFeaturesHolder->enabledFeatures.features.samplerAnisotropy = availableFeatures.features.samplerAnisotropy;
	createInfo.pEnabledFeatures = &enabledFeaturesHolder->enabledFeatures.features;
	createInfo.pNext = enabledFeaturesHolder->enabledFeatures.pNext;

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

	return std::make_shared<Device>(device, data_->choosedDevice->getPhysicalDevice(), queue, transmitQueue, extensions_, std::move(enabledFeaturesHolder));
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
	auto surface = surface_.lock();
	if (!surface)
	{
		throw std::runtime_error("Surface gone...");
		return;
	}
	for (auto physicalDevice : data_->physicalDevices)
	{
		uint32_t queueCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueFamilyProperties.data());
		
		uint32_t queueFamilyIndex = UINT32_MAX;

		for (uint32_t queueFamilyCurrentIndex = 0; queueFamilyCurrentIndex < queueFamilyProperties.size(); queueFamilyCurrentIndex++)
		{
			VkBool32 supported;
			if (vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyCurrentIndex, surface->getSurface(), &supported) == VK_SUCCESS)
			{
				if (!supported)
					continue;
			}

			auto props = queueFamilyProperties[queueFamilyCurrentIndex];
			if (!(props.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT)))
				continue;
			queueFamilyIndex = queueFamilyCurrentIndex;
			break;
		}

		data_->choosedDevice = std::make_shared<PhysicalDevice>(physicalDevice);
		surface->init(physicalDevice);
		data_->queueFamilyIndex = queueFamilyIndex;
		break;
	}
}
