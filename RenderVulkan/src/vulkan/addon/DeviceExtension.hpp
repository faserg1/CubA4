#ifndef RENDERVULKAN_DEVICEEXTENSION_HPP
#define RENDERVULKAN_DEVICEEXTENSION_HPP

#include <memory>
#include "DeviceAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct DeviceExtensionData;

				class DeviceExtension :
					public DeviceAddon
				{
				public:
					explicit DeviceExtension(std::weak_ptr<PhysicalDevice> physicalDevice);
					~DeviceExtension();
				protected:
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<DeviceExtensionData> data_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_DEVICEEXTENSION_HPP
