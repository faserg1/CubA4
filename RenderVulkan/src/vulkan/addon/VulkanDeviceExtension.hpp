#ifndef VULKANDEVICEEXTENSION_HPP
#define VULKANDEVICEEXTENSION_HPP

#include "VulkanDeviceAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanDeviceExtension :
					public VulkanDeviceAddon
				{
				public:
					explicit VulkanDeviceExtension();
					~VulkanDeviceExtension();
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANDEVICEEXTENSION_HPP
