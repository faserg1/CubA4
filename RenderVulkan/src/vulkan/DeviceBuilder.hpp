#ifndef VULKANDEVICEBUILDER_HPP
#define VULKANDEVICEBUILDER_HPP

#include <memory>
#include <vector>
#include <string>

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
			class VulkanPhysicalDevice;
			struct VulkanDeviceBuilderData;

			class VulkanDeviceBuilder
			{
			public:
				explicit VulkanDeviceBuilder(std::shared_ptr<const VulkanInstance> instance,
					std::weak_ptr<const VulkanSurface> surface);
				~VulkanDeviceBuilder();

				void addLayer(addon::VulkanDeviceLayer &layer);
				void addExtension(addon::VulkanDeviceExtension &extension);

				std::weak_ptr<VulkanPhysicalDevice> getPhysicalDevice();

				std::shared_ptr<const VulkanDevice> build();
				void destroy(std::shared_ptr<const VulkanDevice> device);
			protected:
				void enumPhysicalDevices();
				void choosePhysicalDevice();
			private:
				std::shared_ptr<VulkanDeviceBuilderData> data_;
				std::shared_ptr<const VulkanInstance> instance_;
				std::weak_ptr<const VulkanSurface> surface_;

				std::vector<std::string> extensions_;
				std::vector<std::string> layers_;
			};
		}
	}
}

#endif // VULKANDEVICEBUILDER_HPP
