#include "./RenderModel.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::model;
using namespace CubA4::render::vulkan;

RenderModel::RenderModel(std::shared_ptr<const Device> device,
	std::shared_ptr<const Memory> vertexBufferMemory,
	std::shared_ptr<const Memory> indexBufferMemory,
	VkBuffer vertexBuffer,
	VkBuffer indexBuffer) :
	device_(device),
	vertexBufferMemory_(vertexBufferMemory), indexBufferMemory_(indexBufferMemory),
	vertexBuffer_(vertexBuffer), indexBuffer_(indexBuffer)
{
	
}

RenderModel::~RenderModel()
{
	vkDestroyBuffer(device_->getDevice(), vertexBuffer_, nullptr);
	vkDestroyBuffer(device_->getDevice(), indexBuffer_, nullptr);
}

void RenderModel::bind(VkCommandBuffer cmdBuffer, uint32_t index)
{
	const VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBuffer, index, 1, &vertexBuffer_, &offset);
	vkCmdBindIndexBuffer(cmdBuffer, indexBuffer_, offset, VK_INDEX_TYPE_UINT16);
}