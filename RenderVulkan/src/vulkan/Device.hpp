#ifndef DEVICE_HPP 
#define DEVICE_HPP 
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device 
			{
			public:
				explicit Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue);
				~Device();

				VkDevice getDevice() const;
				VkPhysicalDevice getPhysicalDevice() const;
				VkQueue getQueue() const;
			protected:
			private:
				VkDevice device_;
				VkPhysicalDevice physicalDevice_;
				VkQueue queue_;
			};
		}
	}
}

#endif // DEVICE_HPP
