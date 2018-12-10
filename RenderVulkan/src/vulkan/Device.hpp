#ifndef RENDERVULKAN_DEVICE_HPP 
#define RENDERVULKAN_DEVICE_HPP 
#include <vulkan/vulkan.h>

#include "DebugMarker.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class DebugMarker;

			class Device
			{
			public:
				explicit Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue);
				~Device();

				VkDevice getDevice() const;
				VkPhysicalDevice getPhysicalDevice() const;
				VkQueue getQueue() const;

				DebugMarker &getMarker() const;
			protected:
			private:
				VkDevice device_;
				VkPhysicalDevice physicalDevice_;
				VkQueue queue_;
				mutable DebugMarker marker_;
			};
		}
	}
}

#endif // RENDERVULKAN_DEVICE_HPP
