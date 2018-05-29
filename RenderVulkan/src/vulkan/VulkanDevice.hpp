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
				explicit VulkanDevice(VkDevice device);
				~VulkanDevice();
				VkDevice getDevice() const;
			protected:
			private:
				VkDevice device_;
				VkQueue renderQueue;
				VkQueue presentQueue;
			};
		}
	}
}

#endif // VULKANDEVICE_HPP
