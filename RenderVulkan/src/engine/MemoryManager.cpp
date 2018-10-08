#include "./MemoryManager.hpp"
#include "../vulkan/Device.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

MemoryManager::MemoryManager(std::shared_ptr<const Device> device) :
	device_(device)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	vkCreateCommandPool(device->getDevice(), &poolInfo, nullptr, &transitPool_);
}

MemoryManager::~MemoryManager()
{
	vkDestroyCommandPool(device_->getDevice(), transitPool_, nullptr);
}

std::shared_future<bool> MemoryManager::copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size)
{
	VkCommandBuffer copyCmd;
	VkFence bufferCopyDone;
	if (!allocateCmdBuffer(copyCmd, bufferCopyDone))
	{
		return {};
	}

	device_->getMarker().setName(bufferCopyDone, "Fence buffer copy awaiter");
	device_->getMarker().setName(copyCmd, "Command buffer for copy buffer");

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(copyCmd, &beginInfo);
	VkBufferCopy region = {};
	region.dstOffset = 0;
	region.srcOffset = 0;
	region.size = size;
	vkCmdCopyBuffer(copyCmd, src, dst, 1, &region);
	vkEndCommandBuffer(copyCmd);

	return submitCmdBuffer(copyCmd, bufferCopyDone);
}

bool MemoryManager::allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence)
{
	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	if (vkCreateFence(device_->getDevice(), &fenceInfo, nullptr, &fence) != VK_SUCCESS)
		return false;
	
	VkCommandBufferAllocateInfo allocateInfo = {};
	allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.commandPool = transitPool_;
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(device_->getDevice(), &allocateInfo, &cmdBuffer) != VK_SUCCESS)
	{
		vkDestroyFence(device_->getDevice(), fence, nullptr);
		return false;
	}
	return true;
}

std::shared_future<bool> MemoryManager::submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence)
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cmdBuffer;

	vkQueueSubmit(device_->getQueue(), 1, &submitInfo, fence);

	return std::async(std::launch::async, [=]() -> bool
	{
		bool result = false;
		if (vkWaitForFences(device_->getDevice(), 1, &fence, VK_TRUE, VK_WHOLE_SIZE) == VK_SUCCESS)
			result = true;
		vkDestroyFence(device_->getDevice(), fence, nullptr);
		vkFreeCommandBuffers(device_->getDevice(), transitPool_, 1, &cmdBuffer);
		return result;
	}).share();
}