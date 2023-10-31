#pragma once

#include <memory>
#include <mutex>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>

namespace CubA4::render::vulkan
{
	class QueryPool
	{
	public:
		explicit QueryPool(std::shared_ptr<const Device> device, VkQueryType type, uint32_t count, VkQueryPipelineStatisticFlags stats = 0);
		~QueryPool();

		void cmdWriteTimestamp(VkCommandBuffer cmd, VkPipelineStageFlags2 pipelineFlags, uint32_t query);
		void cmdReset(VkCommandBuffer cmd, uint32_t firstQuery, uint32_t queryCount);
		void cmdCopyDataToBufferRaw(VkCommandBuffer cmd, uint32_t firstQuery, uint32_t queryCount,
			VkBuffer buffer, VkDeviceSize offset, VkDeviceSize stride, VkQueryResultFlags flags);

		VkResult copyToDataRaw(uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void *data, VkDeviceSize stride, VkQueryResultFlags flags);
		void reset(uint32_t firstQuery, uint32_t queryCount);
	private:
		const std::shared_ptr<const Device> device_;
		VkQueryPool pool_;
	};
}
