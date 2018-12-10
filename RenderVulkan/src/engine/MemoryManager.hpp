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
		}

		namespace engine
		{
			// TODO: [OOKAMI] Класс будет хранить и распределять участки памяти определённого типа

			class MemoryManager
			{
			public:
				explicit MemoryManager(std::shared_ptr<const vulkan::Device> device);
				~MemoryManager();

				std::shared_future<bool> copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				VkCommandPool transitPool_;
			private:
				bool allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence);
				std::shared_future<bool> submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence);
			};
		}
	}
}

#endif // RENDERVULKAN_MEMORYMANAGER_HPP
