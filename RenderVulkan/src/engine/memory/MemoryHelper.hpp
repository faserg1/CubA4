#pragma once

#include <memory>
#include <future>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/CommandPool.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/Fence.hpp>
#include <atomic>

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
		struct ConcurencyData
		{
			ConcurencyData() = default;
			std::shared_ptr<CubA4::render::vulkan::CommandPool> cmdPool {};
			std::shared_ptr<CubA4::render::vulkan::Fence> fence {};
			VkCommandBuffer transitBuffer = nullptr;
			std::unique_ptr<const CubA4::render::vulkan::CommandPool::CommandPoolLock> lock;
		};
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
		std::vector<ConcurencyData> concurency_;
	private:
		bool allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence, ConcurencyData *&data);
		std::shared_future<bool> submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence, ConcurencyData &data);
	};
}
