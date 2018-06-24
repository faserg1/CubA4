#ifndef VULKANDEVICEADDON_HPP
#define VULKANDEVICEADDON_HPP

#include <memory>
#include "Addon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice;
			class VulkanDeviceBuilder;
			class VulkanPhysicalDevice;

			namespace addon
			{
				class VulkanDeviceAddon :
					public VulkanAddon
				{
				public:
					explicit VulkanDeviceAddon(std::weak_ptr<VulkanPhysicalDevice> physicalDevice);
					~VulkanDeviceAddon();

					VulkanAddonType type() const override;
					virtual void init(std::shared_ptr<const VulkanDevice> instance) = 0;
					virtual void destroy(std::shared_ptr<const VulkanDevice> instance) = 0;
					virtual void added(VulkanDeviceBuilder &builder) = 0;
				protected:
					std::weak_ptr<VulkanPhysicalDevice> physicalDevice_;
				private:
				};
			}
		}
	}
}

#endif // VULKANDEVICEADDON_HPP
