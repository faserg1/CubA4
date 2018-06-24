#ifndef VULKANDEVICE_HPP
#define VULKANDEVICE_HPP

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice
			{
			public:
				explicit VulkanDevice(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue);
				~VulkanDevice();

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

#endif // VULKANDEVICE_HPP
