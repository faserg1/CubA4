#ifndef RENDERVULKAN_DEVICELAYER_HPP
#define RENDERVULKAN_DEVICELAYER_HPP

#include "DeviceAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class DeviceLayer :
					public DeviceAddon
				{
				public:
					explicit DeviceLayer(std::weak_ptr<PhysicalDevice> physicalDevice);
					~DeviceLayer();
				protected:
				private:
				};
			}
		}
	}
}

#endif // RENDERVULKAN_DEVICELAYER_HPP
