#ifndef RENDERVULKAN_MEMORYALLOCATOR_HPP
#define RENDERVULKAN_MEMORYALLOCATOR_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			class Memory;
		}

		namespace engine
		{
			namespace memory
			{
				enum class MemoryAllocationPrefered
				{
					Device,
					Host
				};

				class MemoryAllocator
				{
				public:
					explicit MemoryAllocator(std::shared_ptr<const vulkan::Device> device);
					~MemoryAllocator();

					std::shared_ptr<vulkan::Memory> allocate(size_t size, MemoryAllocationPrefered preference, uint32_t supportedTypes);
					std::shared_ptr<vulkan::Memory> allocateAndBind(VkBuffer buffer, MemoryAllocationPrefered preference);
					std::shared_ptr<vulkan::Memory> allocateAndBind(VkImage image, MemoryAllocationPrefered preference);
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MEMORYALLOCATOR_HPP
