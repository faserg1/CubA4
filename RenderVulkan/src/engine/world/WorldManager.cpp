#include "./WorldManager.hpp"
#include "../ResourceManager.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../memory/MemoryAllocator.hpp"
#include "../memory/MemoryManager.hpp"
#include "../memory/MemoryHelper.hpp"

#include <engine/world/Camera.hpp>
#include <world/Position.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::util;

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

std::shared_ptr<ICamera> WorldManager::createCamera()
{
	return std::make_shared<Camera>();
}

void WorldManager::setActiveCamera(std::shared_ptr<ICamera> camera)
{
	auto activeCamera = activeCamera_.lock();
	if (activeCamera)
		activeCamera->setActive(false);
	if (camera)
	{
		auto rcamera = std::dynamic_pointer_cast<Camera>(camera);
		rcamera->setActive(true);
		activeCamera_ = rcamera;
	}
	else
		activeCamera_.reset();
}

void WorldManager::setFieldOfView(float degrees)
{
	worldData_.projectionFov = static_cast<float>(degrees * glm::pi<float>() / 360);
	updateProjectionMatrix();
}

Ray WorldManager::getRayFrom(uint64_t x, uint64_t y, std::shared_ptr<const ICamera> camera) const
{
	if (!camera)
		camera = activeCamera_.lock();
	if (!camera)
		return {};
	auto rcamera = std::dynamic_pointer_cast<const Camera>(camera);
	const auto &matrix = rcamera->getViewMatrix();
	// TODO: ??

	float ndcX = (2.f * x) / worldData_.projectionWidth - 1.f;
    float ndcY = 1.f - (2.f * y) / worldData_.projectionHeight;

	auto matrixProj = worldData_.projMatrix_;
	matrixProj[1][1] *= -1;
	glm::mat4 inverseProj = glm::inverse(matrixProj);
	glm::mat4 inverseView = glm::inverse(matrix);

	glm::vec4 viewSpace = inverseProj * glm::vec4(ndcX, ndcY, 1.f, 1.f);

	glm::vec4 worldSpace = inverseView * viewSpace;

	glm::vec3 rayDirection = glm::normalize(glm::vec3(worldSpace));

	return Ray {
		.position = camera->getPosition(),
		.direction = CubA4::world::BasePos<float>(rayDirection.x, rayDirection.y, rayDirection.z)
	};
}

void WorldManager::onViewportUpdate(uint64_t width, uint64_t height)
{
	worldData_.projectionWidth = static_cast<float>(width);
	worldData_.projectionHeight = static_cast<float>(height);
	updateProjectionMatrix();
}

void WorldManager::onFrameUpdate()
{
	auto activeCamera = activeCamera_.lock();
	if (!activeCamera)
		return;
	const auto &matrix = activeCamera->getViewMatrix();
	const auto &chunkPos = activeCamera->getChunkPos();
	memoryHelper_->updateBuffer(&chunkPos, worldBuffer_->get(), 0, sizeof(CubA4::world::ChunkPos), BufferBarrierType::Uniform).wait();
	VkDeviceSize matrixSize = sizeof(float) * 16;
	VkDeviceSize offset = memoryManager_->calcAlign(sizeof(CubA4::world::ChunkPos), 16);
	memoryHelper_->updateBuffer(glm::value_ptr(matrix), worldBuffer_->get(), offset, matrixSize, BufferBarrierType::Uniform).wait();
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
		// NOTE: [OOKAMI] Отдельно освобождать сет не нужно, но трогдать пул точно не стоит
		//vkFreeDescriptorSets(dev->getDevice(), p->get(), 1, &set);
	};

	worldSet_ = createSharedVulkanObject(set, deleter);
}

void WorldManager::allocateBuffers()
{
	VkDeviceSize matrixSize = sizeof(float) * 16;

	VkBuffer worldBuffer = {};
	VkBufferCreateInfo worldBufferInfo = {};
	worldBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	worldBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	worldBufferInfo.size = memoryManager_->calcAlign(sizeof(CubA4::world::ChunkPos), 16) + matrixSize + matrixSize; // view global pos + view matrix + projection matrix

	if (vkCreateBuffer(device_->getDevice(), &worldBufferInfo, nullptr, &worldBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}

	device_->getMarker().setName(worldBuffer, "worldBuffer");

	VkMemoryRequirements req = {};
	vkGetBufferMemoryRequirements(device_->getDevice(), worldBuffer, &req);

	auto memory = memoryAllocator_->allocate(req.size, MemoryAllocationPrefered::Device, req.memoryTypeBits);
	vkBindBufferMemory(device_->getDevice(), worldBuffer, memory->getMemory(), 0);

	// memory will be destroyed after the buffer
	std::function<void(VkBuffer)> deleter = [memory, dev = device_](VkBuffer buffer)
	{
		vkDestroyBuffer(dev->getDevice(), buffer, nullptr);
	};
	worldBuffer_ = createSharedVulkanObject(worldBuffer, deleter);
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

void WorldManager::updateProjectionMatrix()
{
	// TODO: [OOKAMI] Set normal aspect ratio
	worldData_.projMatrix_ = glm::perspectiveFovRH(worldData_.projectionFov, worldData_.projectionWidth, worldData_.projectionHeight, 0.01f, 16.f * CubA4::world::ChunkSize);
	worldData_.projMatrix_[1][1] *= -1;
	VkDeviceSize matrixSize = sizeof(float) * 16;
	VkDeviceSize offset = memoryManager_->calcAlign(sizeof(CubA4::world::ChunkPos), 16) + matrixSize;
	memoryHelper_->updateBuffer(glm::value_ptr(worldData_.projMatrix_), worldBuffer_->get(), offset, matrixSize, BufferBarrierType::Uniform).wait();
}