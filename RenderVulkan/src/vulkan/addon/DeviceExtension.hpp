#ifndef VULKANDEVICEEXTENSION_HPP
#define VULKANDEVICEEXTENSION_HPP

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
				struct VulkanDeviceExtensionData;

				class VulkanDeviceExtension :
					public VulkanDeviceAddon
				{
				public:
					explicit VulkanDeviceExtension(std::weak_ptr<VulkanPhysicalDevice> physicalDevice);
					~VulkanDeviceExtension();
				protected:
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<VulkanDeviceExtensionData> data_;
				};
			}
		}
	}
}

#endif // VULKANDEVICEEXTENSION_HPP
