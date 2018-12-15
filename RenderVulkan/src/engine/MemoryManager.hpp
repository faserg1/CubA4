#ifndef RENDERVULKAN_MEMORYMANAGER_HPP
#define RENDERVULKAN_MEMORYMANAGER_HPP

#include <map>
#include <memory>
#include <future>
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
			// TODO: [OOKAMI] Класс будет хранить и распределять участки памяти определённого типа

			class IMemoryBlock
			{
			public:
				virtual VkMemoryPropertyFlags getFlags() const = 0;
				virtual uint32_t getMemoryTypeIndex() const = 0;
			protected:
				IMemoryBlock() = default;
				virtual ~IMemoryBlock() = default;
			};

			class IMemoryPart
			{
			public:
				virtual std::shared_ptr<vulkan::Memory> getMemory() const = 0;
				virtual VkDeviceSize getOffset() const = 0;
				virtual VkDeviceSize getSize() const = 0;
				virtual std::shared_ptr<const IMemoryBlock> getBlock() const = 0;
			protected:
				IMemoryPart() = default;
				virtual ~IMemoryPart() = default;
			};

			class MemoryAllocator;
			class MemoryManager
			{
			public:
				explicit MemoryManager(std::shared_ptr<const vulkan::Device> device, uint32_t blockSize = 8 * 1024 * 1024);
				~MemoryManager();

				std::shared_future<bool> copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
				std::shared_future<bool> updateBuffer(void *data, VkBuffer dst, VkDeviceSize offset, VkDeviceSize size);

				uint32_t calcAlign(uint32_t size, uint32_t align);

				std::shared_ptr<const IMemoryPart> allocatePart(uint64_t size, uint64_t alignment, uint32_t supportedTypes);
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<MemoryAllocator> allocator_; ///< Собственный аллокатор для менеджера
				const uint32_t blockSize_;
				VkCommandPool transitPool_;
				std::vector<std::shared_ptr<IMemoryBlock>> memoryBlocks_;
			private:
				bool allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence);
				std::shared_future<bool> submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence);

				std::shared_ptr<IMemoryBlock> allocateBlock(uint32_t supportedTypes);
			};
		}
	}
}

#endif // RENDERVULKAN_MEMORYMANAGER_HPP
