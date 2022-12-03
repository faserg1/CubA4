#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <vulkan/Instance.hpp>

namespace CubA4::render::vulkan
{
	class Surface
	{
	public:
		explicit Surface(std::shared_ptr<const Instance> instance, VkSurfaceKHR surafece);
		~Surface();

		void init(VkPhysicalDevice device);
		VkSurfaceKHR getSurface() const;

		VkSurfaceCapabilitiesKHR getCapabilities() const;
		const std::vector<VkSurfaceFormatKHR> &surfaceFormats() const;
		const std::vector<VkPresentModeKHR> &presentModes() const;
	protected:
	private:
		std::shared_ptr<const Instance> instance_;
		const VkSurfaceKHR surface_;
		VkPhysicalDevice device_;

		std::vector<VkSurfaceFormatKHR> surfaceFormats_;
		std::vector<VkPresentModeKHR> presentModes_;
	};
}

