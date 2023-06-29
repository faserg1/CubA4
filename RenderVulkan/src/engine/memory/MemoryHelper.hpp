#pragma once

#include <memory>
#include <future>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>
#include <mutex>

namespace tf
{
	class Task;
	class Taskflow;
}

namespace CubA4::render::engine::memory
{
	enum class BufferBarrierType
	{
		None,
		Vertex,
		Uniform,
	};

	class MemoryHelper
	{
		struct Queue;
	public:
		explicit MemoryHelper(std::shared_ptr<const vulkan::Device> device);
		~MemoryHelper();

		std::future<void> copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
		std::future<void> copyBufferToImage(VkBuffer src, VkImage dst, std::vector<VkBufferImageCopy> regions,
			VkImageLayout srcLayout, VkImageLayout dstLayout, VkImageSubresourceRange subresourceRange);
		std::future<void> updateBuffer(const void *data, VkBuffer dst, VkDeviceSize offset, VkDeviceSize size, BufferBarrierType bufferBarrierType = BufferBarrierType::None);
	protected:
	private:
		std::shared_ptr<const vulkan::Device> device_;
		std::vector<std::unique_ptr<Queue>> queues_;
		std::mutex queueMutex_;
		size_t currentQueue_ = 0;
	private:
		Queue *getNextQueue();
		void submitCmdBuffer(Queue *queue, tf::Taskflow *flow, tf::Task *prev);
	};
}
