#ifndef VULKANDEVICELAYER_HPP
#define VULKANDEVICELAYER_HPP

#include "VulkanDeviceAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanDeviceLayer :
					public VulkanDeviceAddon
				{
				public:
					explicit VulkanDeviceLayer();
					~VulkanDeviceLayer();
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANDEVICELAYER_HPP