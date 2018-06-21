#ifndef DEVICEADDON_HPP 
#define DEVICEADDON_HPP 
#include <memory>
#include "Addon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device; 
			class DeviceBuilder; 
			class PhysicalDevice;

			namespace addon
			{
				class DeviceAddon : 
					public Addon
				{
				public:
					explicit DeviceAddon(std::weak_ptr<PhysicalDevice> physicalDevice);
					~DeviceAddon();

					AddonType type() const override;
					virtual void init(std::shared_ptr<const Device> instance) = 0;
					virtual void destroy(std::shared_ptr<const Device> instance) = 0;
					virtual void added(DeviceBuilder &builder) = 0;
				protected:
					std::weak_ptr<PhysicalDevice> physicalDevice_;
				private:
				};
			}
		}
	}
}

#endif // DEVICEADDON_HPP 
