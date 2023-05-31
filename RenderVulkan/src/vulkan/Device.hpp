#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <mutex>
#include "DebugMarker.hpp"

namespace CubA4::render::vulkan
{
	class DebugMarker;

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
		explicit Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkQueue transmit, std::vector<std::string> extensions, VkPhysicalDeviceFeatures2 enabledFeatures);
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
		VkPhysicalDeviceFeatures2 enabledFeatures_;
		struct QueueData
		{
			VkQueue queue;
			mutable std::mutex mutex;
		} renderQueue_, transmitQueue_;
		mutable DebugMarker marker_;
	};
}
