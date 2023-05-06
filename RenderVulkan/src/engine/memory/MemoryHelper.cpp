#include "./MemoryHelper.hpp"
#include "../../vulkan/Device.hpp"
#include <taskflow/taskflow.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/Fence.hpp>
#include <thread>
#include <cmath>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

struct MemoryHelper::Queue
{
	Queue(std::shared_ptr<const vulkan::Device> device) : executor(1)
	{
		cmdPool = std::make_shared<CommandPool>(device, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		fence = std::make_shared<Fence>(device, 0);
		cmdPool->allocate(1, &transitBuffer);
	}
	std::shared_ptr<CubA4::render::vulkan::CommandPool> cmdPool {};
	std::shared_ptr<CubA4::render::vulkan::Fence> fence {};
	VkCommandBuffer transitBuffer = nullptr;
	tf::Executor executor;
};

MemoryHelper::MemoryHelper(std::shared_ptr<const Device> device) :
	device_(device), queueRotation_(0)
{
	for (size_t i = 0; i < std::max(std::thread::hardware_concurrency(), 4u); i++)
		queues_.push_back(std::make_unique<Queue>(device_));
}

MemoryHelper::~MemoryHelper()
{
}

std::future<void> MemoryHelper::copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size)
{
	auto queue = getNextQueue();

	tf::Taskflow flow;

	auto record = flow.emplace([queue, src, dst, size]{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		vkBeginCommandBuffer(queue->transitBuffer, &beginInfo);
		VkBufferCopy region = {};
		region.dstOffset = 0;
		region.srcOffset = 0;
		region.size = size;
		vkCmdCopyBuffer(queue->transitBuffer, src, dst, 1, &region);
		vkEndCommandBuffer(queue->transitBuffer);
	});

	submitCmdBuffer(queue, &flow, &record);
	return queue->executor.run(std::move(flow));
}

std::future<void> MemoryHelper::copyBufferToImage(VkBuffer src, VkImage dst, std::vector<VkBufferImageCopy> regions,
	VkImageLayout srcLayout, VkImageSubresourceRange subresourceRange)
{
	auto queue = getNextQueue();

	tf::Taskflow flow;
	auto record = flow.emplace([queue, src, dst, r = std::move(regions), srcLayout, subresourceRange]{
		VkImageMemoryBarrier inMemoryBarrier = {};
		inMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		inMemoryBarrier.oldLayout = srcLayout;
		inMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		inMemoryBarrier.image = dst;
		inMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		inMemoryBarrier.subresourceRange = subresourceRange;

		VkImageMemoryBarrier outMemoryBarrier = {};
		outMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		outMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		outMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; // TODO: get the layout from params
		outMemoryBarrier.image = dst;
		outMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		outMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		outMemoryBarrier.subresourceRange = subresourceRange;

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		vkBeginCommandBuffer(queue->transitBuffer, &beginInfo);
		vkCmdPipelineBarrier(queue->transitBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &inMemoryBarrier);
		vkCmdCopyBufferToImage(queue->transitBuffer, src, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(r.size()), r.data());
		vkCmdPipelineBarrier(queue->transitBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
			0, nullptr,
			0, nullptr,
			1, &outMemoryBarrier);
		vkEndCommandBuffer(queue->transitBuffer);
	});
	

	submitCmdBuffer(queue, &flow, &record);
	return queue->executor.run(std::move(flow));
}

std::future<void> MemoryHelper::updateBuffer(const void *data, VkBuffer dst, VkDeviceSize offset, VkDeviceSize size, BufferBarrierType bufferBarrierType)
{
	auto queue = getNextQueue();

	tf::Taskflow flow;
	auto record = flow.emplace([queue, data, dst, offset, size, bufferBarrierType]{
		VkBufferMemoryBarrier bufferBarier = {};
		bufferBarier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
		bufferBarier.buffer = dst;
		bufferBarier.size = size;
		bufferBarier.offset = offset;
		bufferBarier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		VkPipelineStageFlags stageFlags = {};

		switch (bufferBarrierType)
		{
		case BufferBarrierType::Vertex:
			bufferBarier.dstAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
			stageFlags = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
			break;
		case BufferBarrierType::Uniform:
			bufferBarier.dstAccessMask = VK_ACCESS_UNIFORM_READ_BIT;
			stageFlags = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; // before the all shaders stages
			break;
		default:
			break;
		}

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		vkBeginCommandBuffer(queue->transitBuffer, &beginInfo);
		vkCmdUpdateBuffer(queue->transitBuffer, dst, offset, size, data);
		if (bufferBarrierType != BufferBarrierType::None)
		{
			vkCmdPipelineBarrier(queue->transitBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, stageFlags, 0,
				0, nullptr,
				1, &bufferBarier,
				0, nullptr);
		}

		vkEndCommandBuffer(queue->transitBuffer);

	});
	
	submitCmdBuffer(queue, &flow, &record);
	return queue->executor.run(std::move(flow));
}

MemoryHelper::Queue *MemoryHelper::getNextQueue()
{
	auto idx = queueRotation_.fetch_add(1);
	if (idx >= queues_.size())
	{
		auto count = static_cast<unsigned char>(queues_.size());
		queueRotation_.fetch_sub(count);
		idx -= count;
	}
	return queues_[idx].get();
}

void MemoryHelper::submitCmdBuffer(Queue *queue, tf::Taskflow *flow, tf::Task *prev)
{
	auto submit = flow->emplace([queue, this]{
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &queue->transitBuffer;
		auto q = device_->getQueue(QueueType::Transmit);
		vkQueueSubmit(q->get(), 1, &submitInfo, queue->fence->getFence());
	});
	prev->precede(submit);
	auto awaiter = flow->emplace([queue, this]{
		auto fence = queue->fence->getFence();
		vkWaitForFences(device_->getDevice(), 1, &fence, VK_TRUE, VK_WHOLE_SIZE);
		queue->fence->reset();
		vkResetCommandBuffer(queue->transitBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
	});
	submit.precede(awaiter);
}
