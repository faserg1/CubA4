#pragma once

#include <memory>
#include "DeviceAddon.hpp"

namespace CubA4::render::vulkan::addon
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
