#ifndef VULKANDEVICEBUILDER_HPP
#define VULKANDEVICEBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanDeviceLayer;
				class VulkanDeviceExtension;
			}

			class VulkanInstance;
			class VulkanDevice;
			class VulkanSurface;
			struct VulkanDeviceBuilderData;

			class VulkanDeviceBuilder
			{
			public:
				explicit VulkanDeviceBuilder(std::shared_ptr<const VulkanInstance> instance,
					std::weak_ptr<const VulkanSurface> surface);
				~VulkanDeviceBuilder();

				void addLayer(addon::VulkanDeviceLayer &layer);
				void addExtension(addon::VulkanDeviceExtension &extension);
				std::shared_ptr<const VulkanDevice> build();
				void destroy(std::shared_ptr<const VulkanDevice> device);
			protected:
				void enumPhysicalDevices();
				void choosePhysicalDevice();
			private:
				std::shared_ptr<VulkanDeviceBuilderData> data_;
				std::shared_ptr<const VulkanInstance> instance_;
				std::weak_ptr<const VulkanSurface> surface_;
			};
		}
	}
}

#endif // VULKANDEVICEBUILDER_HPP
