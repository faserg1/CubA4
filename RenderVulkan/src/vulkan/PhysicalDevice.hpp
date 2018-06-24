#ifndef VULKANPHYSICALDEVICE_HPP
#define VULKANPHYSICALDEVICE_HPP

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanPhysicalDevice
			{
			public:
				explicit VulkanPhysicalDevice(VkPhysicalDevice physicalDevice);
				~VulkanPhysicalDevice();

				VkPhysicalDevice getPhysicalDevice() const;
			protected:
			private:
				VkPhysicalDevice physicalDevice_;
			};
		}
	}
}

#endif // VULKANPHYSICALDEVICE_HPP
