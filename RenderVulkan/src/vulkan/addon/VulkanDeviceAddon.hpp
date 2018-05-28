#ifndef VULKANDEVICEADDON_HPP
#define VULKANDEVICEADDON_HPP

#include "VulkanAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanDeviceAddon :
					public VulkanAddon
				{
				public:
					explicit VulkanDeviceAddon();
					~VulkanDeviceAddon();

					VulkanAddonType type() const override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANDEVICEADDON_HPP
