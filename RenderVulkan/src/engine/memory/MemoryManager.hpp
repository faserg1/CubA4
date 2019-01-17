#ifndef RENDERVULKAN_MEMORYMANAGER_HPP
#define RENDERVULKAN_MEMORYMANAGER_HPP

#include <memory>
#include <cstdint>
#include <vector>
#include <mutex>
#include "IMemoryPart.hpp"
#include "IMemoryBlock.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			namespace memory
			{
				class MemoryAllocator;

				class MemoryManager
				{
				public:
					explicit MemoryManager(std::shared_ptr<const vulkan::Device> device, uint32_t blockSize = 8 * 1024 * 1024);
					~MemoryManager();

					uint32_t calcAlign(uint32_t size, uint32_t align);
					std::shared_ptr<const IMemoryPart> allocatePart(uint64_t size, uint64_t alignment, uint32_t supportedTypes);
				protected:
				private:
					std::shared_ptr<const vulkan::Device> device_;
					const uint32_t blockSize_;
					const std::shared_ptr<MemoryAllocator> allocator_; ///< Собственный аллокатор для менеджера
					std::vector<std::shared_ptr<IMemoryBlock>> memoryBlocks_;
					std::mutex mutex_;
				private:
					std::shared_ptr<IMemoryBlock> allocateBlock(uint32_t supportedTypes);
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MEMORYMANAGER_HPP
