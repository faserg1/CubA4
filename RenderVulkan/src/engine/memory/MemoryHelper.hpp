#ifndef RENDERVULKAN_MEMORYHELPER_HPP
#define RENDERVULKAN_MEMORYHELPER_HPP

#include <memory>
#include <future>
#include <vector>
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
			namespace memory
			{
				enum class BufferBarrierType
				{
					None,
					Vertex,
					Uniform,
				};

				class MemoryHelper
				{
				public:
					explicit MemoryHelper(std::shared_ptr<const vulkan::Device> device);
					~MemoryHelper();

					std::shared_future<bool> copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
					std::shared_future<bool> copyBufferToImage(VkBuffer src, VkImage dst, std::vector<VkBufferImageCopy> regions,
						VkImageLayout srcLayout, VkImageSubresourceRange subresourceRange);
					std::shared_future<bool> updateBuffer(void *data, VkBuffer dst, VkDeviceSize offset, VkDeviceSize size, BufferBarrierType bufferBarrierType = BufferBarrierType::None);
				protected:
				private:
					std::shared_ptr<const vulkan::Device> device_;
					VkCommandPool transitPool_;
					VkCommandBuffer transitBuffer_;
					VkFence transitFence_;
				private:
					bool allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence);
					std::shared_future<bool> submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence);
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MEMORYHELPER_HPP
