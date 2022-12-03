#pragma once

#include <vulkan/vulkan.h>

namespace CubA4::render::vulkan
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
