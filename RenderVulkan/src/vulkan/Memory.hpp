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

			class Memory :
				public std::enable_shared_from_this<Memory>
			{
			public:
				explicit Memory(std::shared_ptr<const Device> device, VkDeviceMemory memory, VkDeviceSize size, VkMemoryPropertyFlags flags, uint32_t memoryTypeIndex);
				~Memory();

				bool isMappable() const;
				VkDeviceMemory getMemory() const;
				VkDeviceSize getSize() const;
				VkMemoryPropertyFlags getFlags() const;
				uint32_t getMemoryTypeIndex() const;
				std::shared_ptr<void> map(VkDeviceSize offset, VkDeviceSize size) const;
			protected:
				
			private:
				const std::shared_ptr<const Device> device_;
				const VkDeviceMemory memory_;
				const VkDeviceSize size_;
				const VkMemoryPropertyFlags flags_;
				const uint32_t memoryTypeIndex_;
			};
		}
	}
}

#endif // RENDERVULKAN_MEMORY_HPP
