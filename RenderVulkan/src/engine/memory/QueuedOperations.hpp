#pragma once

#include <memory>
#include <vector>
#include <map>
#include <future>
#include <mutex>
#include <utility>
#include <vulkan/Device.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>
#include <engine/memory/MemoryTypes.hpp>

namespace CubA4::render::engine::memory
{
	class QueuedOperations
	{
		struct QueuedOperation
		{
			VkCommandBuffer operation;
			std::vector<vulkan::sVkBuffer> buffersHolder;
		};
	public:
		struct BufferToBufferCopy
		{
			CubA4::render::vulkan::sVkBuffer src;
			CubA4::render::vulkan::sVkBuffer dst;
			std::vector<VkBufferCopy> regions;
			BufferBarrierType bufferBarrierType = BufferBarrierType::None;
		};
		struct MemoryToBufferCopy
		{
			const void *srcMemory;
			CubA4::render::vulkan::sVkBuffer dst;
			VkDeviceSize offset;
			VkDeviceSize size;
			BufferBarrierType bufferBarrierType = BufferBarrierType::None;
		};
		QueuedOperations(std::shared_ptr<const vulkan::Device> device);

		void queueCopyBufferToBuffer(std::vector<BufferToBufferCopy> buffersToCopy);
		void queueUpdateBuffer(std::vector<MemoryToBufferCopy> bufferToUpdate);
		
		[[nodiscard]] std::future<void> executeAll();
	private:
		void constructBarriers(CubA4::render::vulkan::sVkBuffer buffer, const std::vector<VkBufferCopy> &regions,
			BufferBarrierType bufferBarrierType, std::vector<VkBufferMemoryBarrier2> &barriers);
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		std::vector<QueuedOperation> queuedOperations_;
		std::shared_ptr<vulkan::CommandPool> commandPool_;

		std::mutex queuedOperationMutex_;
	};
}