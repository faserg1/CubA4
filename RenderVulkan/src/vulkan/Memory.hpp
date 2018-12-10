#ifndef RENDERVULKAN_MEMORY_HPP
#define RENDERVULKAN_MEMORY_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class Memory
			{
			public:
				static std::shared_ptr<Memory> create(std::shared_ptr<const Device> device, VkDeviceMemory memory, VkDeviceSize size, VkMemoryPropertyFlags flags);
				~Memory();

				bool isMappable();
				VkDeviceMemory getMemory();
				VkDeviceSize getSize();
				VkMemoryPropertyFlags getFlags();
				std::shared_ptr<void> map(VkDeviceSize offset, VkDeviceSize size);
			protected:
				explicit Memory(std::shared_ptr<const Device> device, VkDeviceMemory memory, VkDeviceSize size, VkMemoryPropertyFlags flags);
			private:
				const std::shared_ptr<const Device> device_;
				std::weak_ptr<Memory> self_;
				const VkDeviceMemory memory_;
				const VkDeviceSize size_;
				const VkMemoryPropertyFlags flags_;
			};
		}
	}
}

#endif // RENDERVULKAN_MEMORY_HPP
