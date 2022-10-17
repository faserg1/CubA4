#include "./WorldManager.hpp"
#include "../ResourceManager.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../memory/MemoryAllocator.hpp"
#include "../memory/MemoryManager.hpp"
#include "../memory/MemoryHelper.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

WorldManager::WorldManager(std::shared_ptr<const Device> device, std::shared_ptr<ResourceManager> resourceManager) :
	device_(device), resourceManager_(resourceManager),
	memoryAllocator_(std::make_shared<MemoryAllocator>(device)),
	memoryManager_(std::make_shared<MemoryManager>(device)),
	memoryHelper_(std::make_shared<MemoryHelper>(device))
{
	pool_ = resourceManager_->getBuiltInPool();
	layout_ = resourceManager_->getWorldLayout();
	allocateSets();
	allocateBuffers();
	writeSets();
}

WorldManager::~WorldManager()
{
}

void WorldManager::setCameraPosition(CubA4::core::world::ChunkPos globalPos, float x, float y, float z)
{
	worldData_.viewGlobalPos = globalPos;
	worldData_.viewX = x;
	worldData_.viewY = y;
	worldData_.viewZ = z;
	updateViewMatrix();
}

void WorldManager::setCameraRotation(float roll, float pitch, float yaw)
{
	worldData_.viewRoll = roll;
	worldData_.viewPitch = pitch;
	worldData_.viewYaw = yaw;
	updateViewMatrix();
}

void WorldManager::setFieldOfView(float degrees)
{
	worldData_.projectionFov = static_cast<float>(degrees * glm::pi<float>() / 360);
	worldData_.projectionWidth = 1024;
	worldData_.projectionHeight = 720;
	updateProjectionMatrix();
}

sVkDescriptorSet WorldManager::getWorldDescriptorSet() const
{
	return worldSet_;
}

void WorldManager::allocateSets()
{
	VkDescriptorSetLayout layouts[] = { layout_->get() };

	VkDescriptorSetAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	info.descriptorPool = pool_->get();
	info.descriptorSetCount = 1;
	info.pSetLayouts = layouts;

	VkDescriptorSet set = {};

	vkAllocateDescriptorSets(device_->getDevice(), &info, &set);

	std::function<void(VkDescriptorSet)> deleter = [dev = device_, p = pool_](VkDescriptorSet set)
	{
		// NOTE: [OOKAMI] Отдельно освобождать сет не нужно, но сохранить пул - стоит
		//vkResetDescriptorPool(dev->getDevice(), p->get(), 0);
		//vkFreeDescriptorSets(dev->getDevice(), p->get(), 1, &set);
	};

	worldSet_ = util::createSharedVulkanObject(set, deleter);
}

void WorldManager::allocateBuffers()
{
	VkDeviceSize matrixSize = sizeof(float) * 16;

	VkBuffer worldBuffer = {};
	VkBufferCreateInfo worldBufferInfo = {};
	worldBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	worldBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	worldBufferInfo.size = memoryManager_->calcAlign(sizeof(CubA4::core::world::ChunkPos), 16) + matrixSize + matrixSize; // view global pos + view matrix + projection matrix

	if (vkCreateBuffer(device_->getDevice(), &worldBufferInfo, nullptr, &worldBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}

	VkMemoryRequirements req = {};
	vkGetBufferMemoryRequirements(device_->getDevice(), worldBuffer, &req);

	auto memory = memoryAllocator_->allocate(req.size, MemoryAllocationPrefered::Device, req.memoryTypeBits);
	vkBindBufferMemory(device_->getDevice(), worldBuffer, memory->getMemory(), 0);

	// memory will be destroyed after the buffer
	std::function<void(VkBuffer)> deleter = [memory, dev = device_](VkBuffer buffer)
	{
		vkDestroyBuffer(dev->getDevice(), buffer, nullptr);
	};
	worldBuffer_ = util::createSharedVulkanObject(worldBuffer, deleter);
}

void WorldManager::writeSets()
{
	VkDescriptorBufferInfo bufferWriteInfo = {};
	bufferWriteInfo.buffer = worldBuffer_->get();
	bufferWriteInfo.range = VK_WHOLE_SIZE;

	VkWriteDescriptorSet writeSet = {};
	writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeSet.dstSet = worldSet_->get();
	writeSet.dstBinding = 0;
	writeSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	writeSet.pBufferInfo = &bufferWriteInfo;
	writeSet.descriptorCount = 1;
	vkUpdateDescriptorSets(device_->getDevice(), 1, &writeSet, 0, nullptr);
}

void WorldManager::updateViewMatrix()
{
	memoryHelper_->updateBuffer(&worldData_.viewGlobalPos, worldBuffer_->get(), 0, sizeof(CubA4::core::world::ChunkPos), BufferBarrierType::Uniform);
	glm::mat4 viewMatrix;
	VkDeviceSize matrixSize = sizeof(float) * 16;

	glm::vec3 up { 0, 1, 0};
	viewMatrix = glm::lookAtRH({ worldData_.viewX, worldData_.viewY, worldData_.viewZ }, {0, 0, 0}, up);

	float vMatrix[4][4];
	memcpy(vMatrix, glm::value_ptr(viewMatrix), sizeof(float) * 16);

	memoryHelper_->updateBuffer(glm::value_ptr(viewMatrix), worldBuffer_->get(), memoryManager_->calcAlign(sizeof(CubA4::core::world::ChunkPos), 16), matrixSize, BufferBarrierType::Uniform);
}

void WorldManager::updateProjectionMatrix()
{
	//TODO: [OOKAMI] Set normal aspect ratio
	glm::mat4 projection = glm::perspectiveFovRH(worldData_.projectionFov, worldData_.projectionWidth, worldData_.projectionHeight, 0.01f, 16.f * 32.f);

	VkDeviceSize matrixSize = sizeof(float) * 16;

	float projMatrix[4][4];
	memcpy(projMatrix, glm::value_ptr(projection), sizeof(float) * 16);

	memoryHelper_->updateBuffer(glm::value_ptr(projection), worldBuffer_->get(), memoryManager_->calcAlign(sizeof(CubA4::core::world::ChunkPos), 16) + matrixSize, matrixSize, BufferBarrierType::Uniform);
}