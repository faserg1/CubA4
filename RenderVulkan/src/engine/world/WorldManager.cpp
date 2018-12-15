#include "./WorldManager.hpp"
#include "../ResourceManager.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../MemoryAllocator.hpp"
#include "../MemoryManager.hpp"

#include "../../math/Math.hpp"

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

WorldManager::WorldManager(std::shared_ptr<const Device> device, std::shared_ptr<ResourceManager> resourceManager) :
	device_(device), resourceManager_(resourceManager),
	memoryAllocator_(std::make_shared<MemoryAllocator>(device)), memoryManager_(std::make_shared<MemoryManager>(device))
{
	pool_ = resourceManager_->getBuiltInPool();
	layout_ = resourceManager_->getBuiltInLayout();
	allocateSets();
	allocateBuffers();
	writeSets();
}

WorldManager::~WorldManager()
{
}

void WorldManager::setCameraPosition(CubA4::mod::world::ChunkPos globalPos, float x, float y, float z)
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
	worldData_.projectionFov = static_cast<float>(degrees * math::Pi / 360);
	updateProjectionMatrix();
}

sVkDescriptorSet WorldManager::getWorldDescriptorSetLayout() const
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
	worldBufferInfo.size = sizeof(CubA4::mod::world::ChunkPos) + matrixSize + matrixSize; // view global pos + view matrix + projection matrix

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
	// TODO: [OOKAMI] Place real buffer
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
	memoryManager_->updateBuffer(&worldData_.viewGlobalPos, worldBuffer_->get(), 0, sizeof(worldData_.viewGlobalPos));
	math::Matrix viewMatrix;
	VkDeviceSize matrixSize = sizeof(float) * 16;

	math::Math::rotateByZ(viewMatrix, worldData_.viewYaw);
	math::Math::rotateByY(viewMatrix, worldData_.viewPitch);
	math::Math::translate(viewMatrix, worldData_.viewX, worldData_.viewY, worldData_.viewZ);

	memoryManager_->updateBuffer(viewMatrix.data(), worldBuffer_->get(), sizeof(worldData_.viewGlobalPos), matrixSize);
}

void WorldManager::updateProjectionMatrix()
{
	//TODO: [OOKAMI] Set normal aspect ratio
	auto projection = math::Math::perspectiveLH(worldData_.projectionFov , worldData_.projectionAspect, 0.01, 16 * 32);

	VkDeviceSize matrixSize = sizeof(float) * 16;

	memoryManager_->updateBuffer(projection.data(), worldBuffer_->get(), sizeof(worldData_.viewGlobalPos) + matrixSize, matrixSize);
}