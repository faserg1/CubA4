#ifndef RENDERVULKAN_DEVICEBUILDER_HPP
#define RENDERVULKAN_DEVICEBUILDER_HPP

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
				class DeviceLayer;
				class DeviceExtension;
			}

			class Instance;
			class Device;
			class Surface;
			class PhysicalDevice;
			struct DeviceBuilderData;

			class DeviceBuilder
			{
			public:
				explicit DeviceBuilder(std::shared_ptr<const Instance> instance,
					std::weak_ptr<Surface> surface);
				~DeviceBuilder();

				void addLayer(addon::DeviceLayer &layer);
				void addExtension(addon::DeviceExtension &extension);

				std::weak_ptr<PhysicalDevice> getPhysicalDevice();

				std::shared_ptr<const Device> build();
				void destroy(std::shared_ptr<const Device> device);
			protected:
				void enumPhysicalDevices();
				void choosePhysicalDevice();
			private:
				std::shared_ptr<DeviceBuilderData> data_;
				std::shared_ptr<const Instance> instance_;
				std::weak_ptr<Surface> surface_;

				std::vector<std::string> extensions_;
				std::vector<std::string> layers_;
			};
		}
	}
}

#endif // RENDERVULKAN_DEVICEBUILDER_HPP
