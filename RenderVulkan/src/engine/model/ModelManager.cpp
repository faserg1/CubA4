#include "./ModelManager.hpp"
#include "../MemoryAllocator.hpp"
#include "../MemoryManager.hpp"
#include "../../vulkan/Memory.hpp"
#include "../../vulkan/Device.hpp"
#include <model/IRenderModelDefinition.hpp>
#include <vulkan/vulkan.h>
using namespace CubA4::render::engine::model;
using namespace CubA4::render::vulkan;

ModelManager::ModelManager(std::shared_ptr<const Device> device) :
	device_(device), allocator_(std::make_shared<MemoryAllocator>(device))
{
	memoryManager_ = std::make_shared<MemoryManager>(device);
}

ModelManager::~ModelManager()
{
	
}

std::shared_ptr<const IRenderModel> ModelManager::registerModel(const CubA4::core::model::IRenderModelDefinition &renderModel)
{
	auto &vertices = renderModel.getVertices();
	auto &faces = renderModel.getFaceIndices();

	VkBuffer vertexBuffer, vertexTransitBuffer;
	VkBuffer indexBuffer, indexTransitBuffer;

	uint64_t verticesSize = vertices.size() * sizeof(CubA4::core::model::Vertex);
	uint64_t indicesSize = 0;

	const unsigned char bufferCount = 4;
	VkBufferCreateInfo bufferInfos[bufferCount] = {};
	for (unsigned char bufferIndex = 0; bufferIndex < bufferCount; bufferIndex++)
	{
		bufferInfos[bufferIndex].sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfos[bufferIndex].sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	VkBufferCreateInfo &vertexBufferInfo = bufferInfos[0], &vertexTransitBufferInfo = bufferInfos[1];
	vertexTransitBufferInfo.size = vertexBufferInfo.size = verticesSize;
	vertexTransitBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	vertexBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

	if (vkCreateBuffer(device_->getDevice(), &vertexTransitBufferInfo, nullptr, &vertexTransitBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
	}
	if (vkCreateBuffer(device_->getDevice(), &vertexBufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
	}

	VkBufferMemoryRequirementsInfo2 reqVertexBufferInfo = {}, reqVertexTransitBufferInfo = {};
	reqVertexBufferInfo.sType = reqVertexTransitBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
	reqVertexTransitBufferInfo.buffer = vertexTransitBuffer;
	reqVertexBufferInfo.buffer = vertexBuffer;

	VkMemoryRequirements2 reqVertexBuffer = {}, reqVertexTransitBuffer = {};
	reqVertexBuffer.sType = reqVertexTransitBuffer.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
	vkGetBufferMemoryRequirements2(device_->getDevice(), &reqVertexTransitBufferInfo, &reqVertexTransitBuffer);
	vkGetBufferMemoryRequirements2(device_->getDevice(), &reqVertexBufferInfo, &reqVertexBuffer);

	auto memoryVertexTransitBuffer = allocator_->allocate(reqVertexTransitBuffer.memoryRequirements.size,
		MemoryAllocationPrefered::Host, reqVertexTransitBuffer.memoryRequirements.memoryTypeBits);
	auto memoryVertexBuffer = allocator_->allocate(reqVertexBuffer.memoryRequirements.size,
		MemoryAllocationPrefered::Device, reqVertexBuffer.memoryRequirements.memoryTypeBits);

	auto mappedMemory = memoryVertexTransitBuffer->map(0, VK_WHOLE_SIZE);
	memcpy(mappedMemory.get(), vertices.data(), verticesSize);
	mappedMemory.reset();

	vkBindBufferMemory(device_->getDevice(), vertexTransitBuffer, memoryVertexTransitBuffer->getMemory(), 0);
	vkBindBufferMemory(device_->getDevice(), vertexBuffer, memoryVertexBuffer->getMemory(), 0);

	memoryManager_->copyBufferToBuffer(vertexTransitBuffer, vertexBuffer, verticesSize);

	return {};
}