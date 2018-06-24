#ifndef PHYSICALDEVICE_HPP
#define PHYSICALDEVICE_HPP

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class PhysicalDevice
			{
			public:
				explicit PhysicalDevice(VkPhysicalDevice physicalDevice);
				~PhysicalDevice();

				VkPhysicalDevice getPhysicalDevice() const;
			protected:
			private:
				VkPhysicalDevice physicalDevice_;
			};
		}
	}
}

#endif // PHYSICALDEVICE_HPP
