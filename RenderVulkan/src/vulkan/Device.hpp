#pragma once

#include <vulkan/vulkan.h>
#include <memory>
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
		explicit Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue, VkQueue transmit);
		~Device();

		VkDevice getDevice() const;
		VkPhysicalDevice getPhysicalDevice() const;
		std::unique_ptr<IQueue> getQueue(QueueType type = QueueType::Render) const;
		//VkQueue getQueue() const;

		DebugMarker &getMarker() const;
	protected:
	private:
		VkDevice device_;
		VkPhysicalDevice physicalDevice_;
		struct QueueData
		{
			VkQueue queue;
			mutable std::mutex mutex;
		} renderQueue_, transmitQueue_;
		mutable DebugMarker marker_;
	};
}
