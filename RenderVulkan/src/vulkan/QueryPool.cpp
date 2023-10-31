#include <vulkan/QueryPool.hpp>
using namespace CubA4::render::vulkan;

QueryPool::QueryPool(std::shared_ptr<const Device> device, VkQueryType type, uint32_t count, VkQueryPipelineStatisticFlags stats) :
	device_(device)
{
	VkQueryPoolCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
	createInfo.queryType = type;
	createInfo.queryCount = count;
	createInfo.pipelineStatistics = stats;
	if (vkCreateQueryPool(device_->getDevice(), &createInfo, nullptr, &pool_) != VK_SUCCESS)
	{
		// TODO: assert?
	}
}

QueryPool::~QueryPool()
{
	vkDestroyQueryPool(device_->getDevice(), pool_, nullptr);
}

void QueryPool::cmdWriteTimestamp(VkCommandBuffer cmd, VkPipelineStageFlags2 pipelineFlags, uint32_t query)
{
	vkCmdWriteTimestamp2(cmd, pipelineFlags, pool_, query);
}

void QueryPool::cmdReset(VkCommandBuffer cmd, uint32_t firstQuery, uint32_t queryCount)
{
	vkCmdResetQueryPool(cmd, pool_, firstQuery, queryCount);
}

void QueryPool::cmdCopyDataToBufferRaw(VkCommandBuffer cmd, uint32_t firstQuery, uint32_t queryCount,
	VkBuffer buffer, VkDeviceSize offset, VkDeviceSize stride, VkQueryResultFlags flags)
{
	vkCmdCopyQueryPoolResults(cmd, pool_, firstQuery, queryCount, buffer, offset, stride, flags);
}

VkResult QueryPool::copyToDataRaw(uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void *data, VkDeviceSize stride, VkQueryResultFlags flags)
{
	return vkGetQueryPoolResults(device_->getDevice(), pool_, firstQuery, queryCount, dataSize, data, stride, flags);
}

void QueryPool::reset(uint32_t firstQuery, uint32_t queryCount)
{
	// Vulkan 1.2
	vkResetQueryPool(device_->getDevice(), pool_, firstQuery, queryCount);
}