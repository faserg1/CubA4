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

			class VulkanDevice;
			struct VulkanDeviceBuilderData;

			class VulkanDeviceBuilder
			{
			public:
				explicit VulkanDeviceBuilder();
				~VulkanDeviceBuilder();

				void addLayer(addon::VulkanDeviceLayer &layer);
				void addExtension(addon::VulkanDeviceExtension &extension);
				std::shared_ptr<const VulkanDevice> build();
				void destroy(std::shared_ptr<const VulkanDevice> instance);
			protected:
			private:
				std::shared_ptr<VulkanDeviceBuilderData> data_;
			};
		}
	}
}

#endif // VULKANDEVICEBUILDER_HPP
