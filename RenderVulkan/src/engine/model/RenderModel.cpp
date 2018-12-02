#include "./RenderModel.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::model;
using namespace CubA4::render::vulkan;

RenderModel::RenderModel(std::shared_ptr<const Device> device, RenderModelData data) :
	device_(device), data_(data)
{
	
}

RenderModel::~RenderModel()
{
	vkDestroyBuffer(device_->getDevice(), data_.vertexBuffer, nullptr);
	vkDestroyBuffer(device_->getDevice(), data_.indexBuffer, nullptr);
}

std::string RenderModel::getId() const
{
	return data_.id;
}

uint32_t RenderModel::getVertexCount() const
{
	return data_.vertexCount;
}

uint32_t RenderModel::getIndexCount() const
{
	return data_.indexCount;
}

void RenderModel::bind(VkCommandBuffer cmdBuffer, uint32_t index) const
{
	const VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmdBuffer, index, 1, &data_.vertexBuffer, &offset);
	vkCmdBindIndexBuffer(cmdBuffer, data_.indexBuffer, offset, VK_INDEX_TYPE_UINT16);
}

