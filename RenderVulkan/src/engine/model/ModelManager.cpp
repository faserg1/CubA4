#include "./ModelManager.hpp"
#include "./RenderModel.hpp"
#include "../MemoryAllocator.hpp"
#include "../MemoryManager.hpp"
#include "../../vulkan/Memory.hpp"
#include "../../vulkan/Device.hpp"
#include <model/IRenderModelDefinition.hpp>
#include <vulkan/vulkan.h>
#include <cstring>
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

std::shared_ptr<const IRenderModel> ModelManager::registerModel(const CubA4::core::model::IRenderModelDefinition &renderModelDef)
{
	auto &vertices = renderModelDef.getVertices();
	auto &faces = renderModelDef.getFaceIndices();

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

	//-------------- Vertex

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

	device_->getMarker().setName(vertexTransitBuffer, "vertex transit buffer");
	device_->getMarker().setName(vertexBuffer, "vertex buffer");

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

	auto mappedVertexMemory = memoryVertexTransitBuffer->map(0, VK_WHOLE_SIZE);
	memcpy(mappedVertexMemory.get(), vertices.data(), verticesSize);
	mappedVertexMemory.reset();

	vkBindBufferMemory(device_->getDevice(), vertexTransitBuffer, memoryVertexTransitBuffer->getMemory(), 0);
	vkBindBufferMemory(device_->getDevice(), vertexBuffer, memoryVertexBuffer->getMemory(), 0);

	memoryManager_->copyBufferToBuffer(vertexTransitBuffer, vertexBuffer, verticesSize);

	vkDestroyBuffer(device_->getDevice(), vertexTransitBuffer, nullptr);

	//-------------- Index

	for (size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++)
	{
		auto verticesCount = faces[faceIndex];
		faceIndex += verticesCount;
		indicesSize += (verticesCount - 2) * 3; // triangle fan
	}

	VkBufferCreateInfo &indexBufferInfo = bufferInfos[2], &indexTransitBufferInfo = bufferInfos[3];
	indexTransitBufferInfo.size = indexBufferInfo.size = indicesSize;
	indexTransitBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	indexBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

	if (vkCreateBuffer(device_->getDevice(), &indexTransitBufferInfo, nullptr, &indexTransitBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
	}
	if (vkCreateBuffer(device_->getDevice(), &indexBufferInfo, nullptr, &indexBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
	}

	device_->getMarker().setName(indexTransitBuffer, "index transit buffer");
	device_->getMarker().setName(indexBuffer, "index buffer");
	
	VkBufferMemoryRequirementsInfo2 reqIndexBufferInfo = {}, reqIndexTransitBufferInfo = {};
	reqIndexBufferInfo.sType = reqIndexTransitBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
	reqIndexTransitBufferInfo.buffer = indexTransitBuffer;
	reqIndexBufferInfo.buffer = indexBuffer;

	VkMemoryRequirements2 reqIndexBuffer = {}, reqIndexTransitBuffer = {};
	reqIndexBuffer.sType = reqIndexTransitBuffer.sType = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;

	vkGetBufferMemoryRequirements2(device_->getDevice(), &reqIndexTransitBufferInfo, &reqIndexTransitBuffer);
	vkGetBufferMemoryRequirements2(device_->getDevice(), &reqIndexBufferInfo, &reqIndexBuffer);

	
	auto memoryIndexTransitBuffer = allocator_->allocate(reqIndexTransitBuffer.memoryRequirements.size,
		MemoryAllocationPrefered::Host, reqIndexTransitBuffer.memoryRequirements.memoryTypeBits);
	auto memoryIndexBuffer = allocator_->allocate(reqIndexBuffer.memoryRequirements.size,
		MemoryAllocationPrefered::Device, reqIndexBuffer.memoryRequirements.memoryTypeBits);

	
	auto mappedIndexMemory = memoryIndexTransitBuffer->map(0, VK_WHOLE_SIZE);
	auto *idxPtr = static_cast<unsigned short*>(mappedIndexMemory.get());
	unsigned short triangleIndices[3] = {};
	auto saveTriangle = [&idxPtr, &triangleIndices]()
	{
		memcpy(idxPtr, triangleIndices, sizeof(triangleIndices));
		idxPtr += 3;
	};
	for (size_t faceIndex = 0, verticesCount = 0, vertexIndex = 0;
		faceIndex < faces.size();
		faceIndex++, verticesCount--, vertexIndex++)
	{
		if (verticesCount == 0)
		{
			verticesCount = faces[faceIndex] + 1; //add + 1 for next iteration
			vertexIndex = -1; //for next iteration
		}
		else
		{
			//save first triangle
			if (vertexIndex == 3)
			{
				saveTriangle();
			}
			//record first triangle
			if (vertexIndex < 3)
			{
				triangleIndices[vertexIndex] = static_cast<unsigned short>(faces[faceIndex]);
			}
			else //record next triangles
			{
				triangleIndices[1] = triangleIndices[2];
				triangleIndices[2] = static_cast<unsigned short>(faces[faceIndex]);
				saveTriangle();
			}
		}
	}
	mappedIndexMemory.reset();

	vkBindBufferMemory(device_->getDevice(), indexTransitBuffer, memoryIndexTransitBuffer->getMemory(), 0);
	vkBindBufferMemory(device_->getDevice(), indexBuffer, memoryIndexBuffer->getMemory(), 0);

	memoryManager_->copyBufferToBuffer(indexTransitBuffer, indexBuffer, indicesSize);

	vkDestroyBuffer(device_->getDevice(), indexTransitBuffer, nullptr);

	return std::make_shared<RenderModel>(device_, memoryVertexBuffer, memoryIndexBuffer, vertexBuffer, indexBuffer, renderModelDef.getId());
}