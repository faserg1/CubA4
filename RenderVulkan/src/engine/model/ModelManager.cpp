#include "./ModelManager.hpp"
#include "./RenderModel.hpp"
#include "../memory/MemoryAllocator.hpp"
#include "../memory/MemoryHelper.hpp"
#include "../../vulkan/Memory.hpp"
#include "../../vulkan/Device.hpp"
#include <vulkan/vulkan.h>
#include <cstring>
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::model;
using namespace CubA4::render::vulkan;

ModelManager::ModelManager(std::shared_ptr<const Device> device) :
	device_(device), allocator_(std::make_shared<MemoryAllocator>(device))
{
	memoryHelper_ = std::make_shared<MemoryHelper>(device);
}

ModelManager::~ModelManager()
{
	
}

std::shared_ptr<const IRenderModel> ModelManager::registerModel(const CubA4::model::IRenderModelDefinition &renderModelDef)
{
	return createModel(renderModelDef);
}

std::shared_ptr<const RenderModel> ModelManager::createModel(const CubA4::model::IRenderModelDefinition &renderModelDef)
{
	auto &vertices = renderModelDef.getVertices();
	auto &uvws = renderModelDef.getUVWCoords();
	auto &faces = renderModelDef.getFaceIndices();
	return createModel(renderModelDef.getId(), vertices, uvws, faces);
}

std::shared_ptr<const RenderModel> ModelManager::createModel(std::string id, const std::vector<Vertex> &vertices, const std::vector<UVWCoords> &uvws, const std::vector<Face> &faces)
{
	if (vertices.size() != uvws.size())
	{
		//TODO: [OOKAMI] Exception — count must be same
		return {};
	}

	VkBuffer vertexBuffer, vertexTransitBuffer;
	VkBuffer indexBuffer, indexTransitBuffer;

	uint64_t verticesSize = ///< Размер буфера вершин, в байтах
		vertices.size() * sizeof(CubA4::model::Vertex) +
		uvws.size() * sizeof(CubA4::model::UVWCoords); 
	uint64_t indexCount = 0; ///< Количество индексов вершин
	uint64_t indicesSize = 0; ///< Размер буфера индексов, в байтах

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
		return {};
	}
	if (vkCreateBuffer(device_->getDevice(), &vertexBufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
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

	/// Fill the vertex buffer
	auto mappedVertexMemory = memoryVertexTransitBuffer->map(0, VK_WHOLE_SIZE);
	for (size_t dstOffset = 0, vIdx = 0; vIdx < vertices.size(); vIdx++)
	{
		auto pushToVBuffer = [&dstOffset, mappedVertexMemory](auto &smth) -> void
		{
			void *ptr = (static_cast<char*>(mappedVertexMemory.get()) + dstOffset);
			auto size = sizeof(smth);
			memcpy(ptr, &smth, size);
			dstOffset += size;
		};
		pushToVBuffer(vertices[vIdx]);
		pushToVBuffer(uvws[vIdx]);
	}
	mappedVertexMemory.reset();

	// Bind and copy

	vkBindBufferMemory(device_->getDevice(), vertexTransitBuffer, memoryVertexTransitBuffer->getMemory(), 0);
	vkBindBufferMemory(device_->getDevice(), vertexBuffer, memoryVertexBuffer->getMemory(), 0);

	memoryHelper_->copyBufferToBuffer(vertexTransitBuffer, vertexBuffer, verticesSize).wait();

	vkDestroyBuffer(device_->getDevice(), vertexTransitBuffer, nullptr);

	//-------------- Index

	for (const auto &face : faces)
	{
		indexCount += (face.indexes.size() - 2) * 3; // triangle fan
	}

	indicesSize = indexCount * sizeof(uint16_t);

	VkBufferCreateInfo &indexBufferInfo = bufferInfos[2], &indexTransitBufferInfo = bufferInfos[3];
	indexTransitBufferInfo.size = indexBufferInfo.size = indicesSize;
	indexTransitBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	indexBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

	if (vkCreateBuffer(device_->getDevice(), &indexTransitBufferInfo, nullptr, &indexTransitBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
	}
	if (vkCreateBuffer(device_->getDevice(), &indexBufferInfo, nullptr, &indexBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
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
	auto *idxPtr = static_cast<uint16_t*>(mappedIndexMemory.get());
	uint16_t triangleIndices[3] = {};
	auto saveTriangle = [&idxPtr, &triangleIndices]()
	{
		memcpy(idxPtr, triangleIndices, sizeof(triangleIndices));
		idxPtr += 3;
	};
	for (auto &face : faces)
	{
		for (size_t vertexIndex = 0; vertexIndex < face.indexes.size(); vertexIndex++)
		{
			//save first triangle
			if (vertexIndex == 3)
			{
				saveTriangle();
			}
			//record first triangle
			if (vertexIndex < 3)
			{
				triangleIndices[vertexIndex] = static_cast<uint16_t>(face.indexes[vertexIndex]);
			}
			else //record next triangles
			{
				triangleIndices[1] = triangleIndices[2];
				triangleIndices[2] = static_cast<uint16_t>(face.indexes[vertexIndex]);
				saveTriangle();
			}
		}
	}
	
	mappedIndexMemory.reset();

	vkBindBufferMemory(device_->getDevice(), indexTransitBuffer, memoryIndexTransitBuffer->getMemory(), 0);
	vkBindBufferMemory(device_->getDevice(), indexBuffer, memoryIndexBuffer->getMemory(), 0);

	memoryHelper_->copyBufferToBuffer(indexTransitBuffer, indexBuffer, indicesSize).wait();

	vkDestroyBuffer(device_->getDevice(), indexTransitBuffer, nullptr);

	RenderModelData rmData = {};
	rmData.vertexBufferMemory = memoryVertexBuffer;
	rmData.indexBufferMemory = memoryIndexBuffer;
	rmData.vertexBuffer = vertexBuffer;
	rmData.indexBuffer = indexBuffer;
	rmData.id = id;
	rmData.vertexCount = static_cast<uint32_t>(vertices.size());
	rmData.indexCount = static_cast<uint32_t>(indexCount);

	return std::make_shared<RenderModel>(device_, rmData);
}