#ifndef VULKANSEMAPHORE_HPP
#define VULKANSEMAPHORE_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice;

			class VulkanSemaphore final
			{
			public:
				explicit VulkanSemaphore(VkSemaphore semaphore, std::weak_ptr<const VulkanDevice> device);
				static std::shared_ptr<VulkanSemaphore> create(std::shared_ptr<const VulkanDevice> device);
				~VulkanSemaphore();

				VkSemaphore getSemaphore() const;
			protected:
			private:
				std::weak_ptr<const VulkanDevice> device_;
				VkSemaphore semaphore_;
			};
		}
	}
}

#endif // VULKANSEMAPHORE_HPP
