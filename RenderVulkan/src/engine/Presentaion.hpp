#ifndef VULKANPRESENTAION_HPP
#define VULKANPRESENTAION_HPP

#include <memory>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice;
			class VulkanSwapchain;
			class VulkanSemaphore;
		}

		namespace engine
		{
			class Presentaion
			{
			public:
				explicit Presentaion(std::shared_ptr<const vulkan::VulkanDevice> device, std::shared_ptr<const vulkan::VulkanSwapchain> swapchain);
				~Presentaion();

				std::shared_ptr<const vulkan::VulkanSemaphore> getAcquireSignalSemaphore() const;
				void addAwaitSemaphore(std::shared_ptr<const vulkan::VulkanSemaphore> semaphore);

				uint32_t acquire();
				void send(uint32_t imageIndex);
			protected:
				
			private:
				std::shared_ptr<const vulkan::VulkanDevice> device_;
				std::shared_ptr<const vulkan::VulkanSwapchain> swapchain_;
				std::shared_ptr<vulkan::VulkanSemaphore> acquireSignalSemaphore_;
				std::vector<std::shared_ptr<const vulkan::VulkanSemaphore>> awaitSemaphores_;
				uint32_t timeout_;
			};
		}
	}
}

#endif // VULKANPRESENTAION_HPP
