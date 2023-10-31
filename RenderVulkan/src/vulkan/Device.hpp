#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <mutex>
#include "DebugMarker.hpp"

namespace CubA4::render::vulkan
{
	class DebugMarker;

	struct DeviceEnabledFeaturesHolder
	{
		VkPhysicalDeviceFeatures2 enabledFeatures = {};
		VkPhysicalDeviceVulkan11Features enabled11Features = {};
		VkPhysicalDeviceVulkan12Features enabled12Features = {};
		VkPhysicalDeviceVulkan13Features enabled13Features = {};
	};

	class IQueue
	{
	public:
		virtual VkQueue get() const = 0;
		virtual ~IQueue() = default;
	protected:
		IQueue() = default;
	};

	enum class QueueType
	{
		Render,
		Transmit
	};

	class Device
	{
	public:
		explicit Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkQueue transmit,
			std::vector<std::string> extensions, std::unique_ptr<DeviceEnabledFeaturesHolder> enabledFeatures);
		~Device();

		VkDevice getDevice() const;
		VkPhysicalDevice getPhysicalDevice() const;
		std::unique_ptr<IQueue> getQueue(QueueType type = QueueType::Render) const;

		const std::vector<std::string> &getEnabledExtensions() const;
		const VkPhysicalDeviceFeatures2 &getEnabledFeatures() const;

		DebugMarker &getMarker() const;
	protected:
	private:
		VkDevice device_;
		VkPhysicalDevice physicalDevice_;

		std::vector<std::string> extensions_;
		const std::unique_ptr<DeviceEnabledFeaturesHolder> enabledFeatures_;
		struct QueueData
		{
			VkQueue queue;
			mutable std::mutex mutex;
		} renderQueue_, transmitQueue_;
		mutable DebugMarker marker_;
	};
}
