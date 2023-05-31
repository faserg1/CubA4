#pragma once 

#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>
#include <vector>

namespace CubA4::render::vulkan
{
	class Swapchain
	{
	public:
		explicit Swapchain(std::shared_ptr<const Device> device, VkSwapchainKHR swapchain, VkExtent2D res, uint32_t imageCount, VkFormat format);
		~Swapchain();

		VkSwapchainKHR getSwapchain() const;
		VkExtent2D getResolution() const;
		uint32_t getImageCount() const;
		VkFormat getFormat() const;
		std::vector<VkImage> getImages() const;
	protected:
	private:
		const std::shared_ptr<const Device> device_;
		VkSwapchainKHR swapchain_;
		VkExtent2D resolution_;
		uint32_t imageCount_;
		VkFormat format_;
	};
}
