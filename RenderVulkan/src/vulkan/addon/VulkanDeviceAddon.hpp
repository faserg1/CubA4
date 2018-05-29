#ifndef VULKANDEVICEADDON_HPP
#define VULKANDEVICEADDON_HPP

#include <memory>
#include "VulkanAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice;
			class VulkanDeviceBuilder;

			namespace addon
			{
				class VulkanDeviceAddon :
					public VulkanAddon
				{
				public:
					explicit VulkanDeviceAddon();
					~VulkanDeviceAddon();

					VulkanAddonType type() const override;
					virtual void init(std::shared_ptr<const VulkanDevice> instance) = 0;
					virtual void destroy(std::shared_ptr<const VulkanDevice> instance) = 0;
					virtual void added(VulkanDeviceBuilder &builder) = 0;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANDEVICEADDON_HPP
