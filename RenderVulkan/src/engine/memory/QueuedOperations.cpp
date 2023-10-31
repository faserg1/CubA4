#include <engine/memory/QueuedOperations.hpp>
#include <vulkan/Fence.hpp>
#include <algorithm>
using namespace CubA4::render::engine::memory;

QueuedOperations::QueuedOperations(std::shared_ptr<const vulkan::Device> device) :
	device_(device), commandPool_(std::make_shared<vulkan::CommandPool>(device, 0))
{

}

void QueuedOperations::queueCopyBufferToBuffer(std::vector<BufferToBufferCopy> buffersToCopy)
{
	QueuedOperation op {};

	auto lockedPool = commandPool_->lock();
	lockedPool->getPool()->allocate(1, &op.operation);
	
	op.buffersHolder.reserve(buffersToCopy.size() * 2);

	std::vector<VkBufferMemoryBarrier2> barriers;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	vkBeginCommandBuffer(op.operation, &beginInfo);
	for (auto &copyInfo : buffersToCopy)
	{
		auto [src, dst, regions, barrierType] = copyInfo;
		vkCmdCopyBuffer(op.operation, src->get(), dst->get(), static_cast<uint32_t>(regions.size()), regions.data());
		op.buffersHolder.push_back(src);
		op.buffersHolder.push_back(dst);

		constructBarriers(dst, regions, barrierType, barriers);
	}

	VkDependencyInfo depsInfo {};
	depsInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	depsInfo.bufferMemoryBarrierCount = static_cast<uint32_t>(barriers.size());
	depsInfo.pBufferMemoryBarriers = barriers.data();

	vkCmdPipelineBarrier2(op.operation, &depsInfo);

	vkEndCommandBuffer(op.operation);

	{
		auto lock = std::unique_lock(queuedOperationMutex_);
		queuedOperations_.push_back(op);
	}
}

void QueuedOperations::queueUpdateBuffer(std::vector<MemoryToBufferCopy> bufferToUpdate)
{
	QueuedOperation op {};

	auto lockedPool = commandPool_->lock();
	lockedPool->getPool()->allocate(1, &op.operation);

	op.buffersHolder.reserve(bufferToUpdate.size());

	std::vector<VkBufferMemoryBarrier2> barriers;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	vkBeginCommandBuffer(op.operation, &beginInfo);

	for (auto &bufferUpdate : bufferToUpdate)
	{
		auto [srcMemory, dst, offset, size, barrierType] = bufferUpdate;
		vkCmdUpdateBuffer(op.operation, dst->get(), offset, size, srcMemory);
		op.buffersHolder.push_back(dst);

		// Fake, to make barrier
		VkBufferCopy region {
			.dstOffset = offset,
			.size = size
		};
		constructBarriers(dst, {region}, barrierType, barriers);
	}

	VkDependencyInfo depsInfo {};
	depsInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	depsInfo.bufferMemoryBarrierCount = static_cast<uint32_t>(barriers.size());
	depsInfo.pBufferMemoryBarriers = barriers.data();

	vkCmdPipelineBarrier2(op.operation, &depsInfo);

	vkEndCommandBuffer(op.operation);

	{
		auto lock = std::unique_lock(queuedOperationMutex_);
		queuedOperations_.push_back(op);
	}
}

std::future<void> QueuedOperations::executeAll()
{
	auto lock = std::unique_lock(queuedOperationMutex_);
	if (queuedOperations_.empty())
		return {};
	std::vector<VkCommandBuffer> allBuffers;
	allBuffers.resize(queuedOperations_.size());
	std::transform(queuedOperations_.begin(), queuedOperations_.end(), allBuffers.begin(), [](const QueuedOperation& op)
	{
		return op.operation;
	});
	auto q = device_->getQueue(CubA4::render::vulkan::QueueType::Transmit);
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = static_cast<uint32_t>(allBuffers.size());
	submitInfo.pCommandBuffers = allBuffers.data();
	
	auto fence = std::make_shared<CubA4::render::vulkan::Fence>(device_);
	device_->getMarker().setName(fence->getFence(), "QueuedOperations::executeAll() fence");
	vkQueueSubmit(q->get(), 1, &submitInfo, fence->getFence());

	return std::async(std::launch::async, [this, fence, ops = std::move(queuedOperations_), buffers = std::move(allBuffers)]()
	{
		fence->wait();
		auto lockedPool = commandPool_->lock();
		lockedPool->getPool()->free(static_cast<uint32_t>(buffers.size()), buffers.data());
	});
}

void QueuedOperations::constructBarriers(CubA4::render::vulkan::sVkBuffer buffer, const std::vector<VkBufferCopy> &regions,
	BufferBarrierType bufferBarrierType, std::vector<VkBufferMemoryBarrier2> &barriers)
{
	if (bufferBarrierType == BufferBarrierType::None)
		return;

	VkBufferMemoryBarrier2 bufferBarier = {};
	bufferBarier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2;
	bufferBarier.buffer = buffer->get();
	bufferBarier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	bufferBarier.srcStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT;

	switch (bufferBarrierType)
	{
	case BufferBarrierType::Vertex:
		bufferBarier.dstAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
		bufferBarier.dstStageMask = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
		break;
	case BufferBarrierType::Uniform:
		bufferBarier.dstAccessMask = VK_ACCESS_UNIFORM_READ_BIT;
		bufferBarier.dstStageMask = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; // before the all shaders stages
		break;
	default:
		break;
	}

	for (auto &region : regions)
	{
		bufferBarier.size = region.size;
		bufferBarier.offset = region.dstOffset;
	}
}