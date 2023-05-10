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
		const VkPhysicalDeviceProperties &getProperties() const;
	protected:
	private:
		VkPhysicalDevice physicalDevice_;
		VkPhysicalDeviceProperties properties_;
	};
}
