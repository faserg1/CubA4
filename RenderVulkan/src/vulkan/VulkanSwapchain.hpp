#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanSwapchain
			{
			public:
				explicit VulkanSwapchain(VkSwapchainKHR swapchain, VkExtent2D res, uint32_t imageCount, VkFormat format);
				~VulkanSwapchain();

				VkSwapchainKHR getSwapchain() const;
				VkExtent2D getResolution() const;
				uint32_t getImageCount() const;
				VkFormat getFormat() const;
			protected:
			private:
				VkSwapchainKHR swapchain_;
				VkExtent2D resolution_;
				uint32_t imageCount_;
				VkFormat format_;
			};
		}
	}
}

#endif // SWAPCHAIN_HPP
