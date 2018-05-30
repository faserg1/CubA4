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
				explicit VulkanDevice(VkDevice device, VkQueue queue);
				~VulkanDevice();

				VkDevice getDevice() const;
				VkQueue getQueue() const;
			protected:
			private:
				VkDevice device_;
				VkQueue queue_;
			};
		}
	}
}

#endif // VULKANDEVICE_HPP
