#include "./MemoryHelper.hpp"
#include "../../vulkan/Device.hpp"
#include <thread>
#include <cmath>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

MemoryHelper::MemoryHelper(std::shared_ptr<const Device> device) :
	device_(device)
{
	concurency_.resize(std::max(std::thread::hardware_concurrency(), 2u));
	for (auto &concurencyData : concurency_)
	{
		concurencyData.cmdPool = std::make_shared<CommandPool>(device_, VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
		concurencyData.fence = std::make_shared<Fence>(device_, 0);
	}
}

MemoryHelper::~MemoryHelper()
{
}

std::shared_future<bool> MemoryHelper::copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size)
{
	VkCommandBuffer copyCmd;
	VkFence bufferCopyDone;
	ConcurencyData *data;
	if (!allocateCmdBuffer(copyCmd, bufferCopyDone, data))
	{
		return {};
	}

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	vkBeginCommandBuffer(copyCmd, &beginInfo);
	VkBufferCopy region = {};
	region.dstOffset = 0;
	region.srcOffset = 0;
	region.size = size;
	vkCmdCopyBuffer(copyCmd, src, dst, 1, &region);
	vkEndCommandBuffer(copyCmd);

	return submitCmdBuffer(copyCmd, bufferCopyDone, *data);
}

std::shared_future<bool> MemoryHelper::copyBufferToImage(VkBuffer src, VkImage dst, std::vector<VkBufferImageCopy> regions,
	VkImageLayout srcLayout, VkImageSubresourceRange subresourceRange)
{
	VkCommandBuffer copyCmd;
	VkFence bufferCopyDone;
	ConcurencyData *data;
	if (!allocateCmdBuffer(copyCmd, bufferCopyDone, data))
	{
		return {};
	}

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
	outMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
	outMemoryBarrier.image = dst;
	outMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	outMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	outMemoryBarrier.subresourceRange = subresourceRange;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	vkBeginCommandBuffer(copyCmd, &beginInfo);
	vkCmdPipelineBarrier(copyCmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
		0, nullptr,
		0, nullptr,
		1, &inMemoryBarrier);
	vkCmdCopyBufferToImage(copyCmd, src, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(regions.size()), regions.data());
	vkCmdPipelineBarrier(copyCmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
		0, nullptr,
		0, nullptr,
		1, &outMemoryBarrier);
	vkEndCommandBuffer(copyCmd);

	return submitCmdBuffer(copyCmd, bufferCopyDone, *data);
}

std::shared_future<bool> MemoryHelper::updateBuffer(void *data, VkBuffer dst, VkDeviceSize offset, VkDeviceSize size, BufferBarrierType bufferBarrierType)
{
	VkCommandBuffer updateCmd;
	VkFence bufferUpdateDone;
	ConcurencyData *cdata;
	if (!allocateCmdBuffer(updateCmd, bufferUpdateDone, cdata))
	{
		return {};
	}

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
	vkBeginCommandBuffer(updateCmd, &beginInfo);
	vkCmdUpdateBuffer(updateCmd, dst, offset, size, data);
	if (bufferBarrierType != BufferBarrierType::None)
	{
		vkCmdPipelineBarrier(updateCmd, VK_PIPELINE_STAGE_TRANSFER_BIT, stageFlags, 0,
			0, nullptr,
			1, &bufferBarier,
			0, nullptr);
	}

	vkEndCommandBuffer(updateCmd);

	return submitCmdBuffer(updateCmd, bufferUpdateDone, *cdata);
}

bool MemoryHelper::allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence, ConcurencyData *&data)
{
	data = nullptr;
	while (!data)
	{
		for (auto &concurencyData : concurency_)
		{
			if (concurencyData.lock)
				continue;
			auto lock = concurencyData.cmdPool->tryLock();
			concurencyData.lock.swap(lock);
			data = &concurencyData;
			break;
		}
	}
	fence = data->fence->getFence();
	if (data->transitBuffer)
	{
		cmdBuffer = data->transitBuffer;
		return true;
	}

	VkCommandBufferAllocateInfo allocateInfo = {};
	allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.commandPool = data->cmdPool->getPool();
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(device_->getDevice(), &allocateInfo, &cmdBuffer) != VK_SUCCESS)
	{
		data->lock.reset();
		return false;
	}

	data->transitBuffer = cmdBuffer;
	
	return true;
}

std::shared_future<bool> MemoryHelper::submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence, ConcurencyData &data)
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cmdBuffer;
	auto q = device_->getQueue(QueueType::Transmit);
	vkQueueSubmit(q->get(), 1, &submitInfo, fence);

	return std::async(std::launch::async, [=, &data]() -> bool
	{
		bool result = false;
		auto lock = std::move(data.lock);
		if (vkWaitForFences(device_->getDevice(), 1, &fence, VK_TRUE, VK_WHOLE_SIZE) == VK_SUCCESS)
			result = true;
		vkResetFences(device_->getDevice(), 1, &fence);
		vkResetCommandBuffer(cmdBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
		return result;
	}).share();
}
