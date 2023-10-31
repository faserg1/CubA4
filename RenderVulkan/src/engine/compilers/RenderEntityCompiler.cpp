#include <engine/compilers/RenderEntityCompiler.hpp>
#include <engine/world/RenderEntity.hpp>
#include <engine/material/MaterialLayout.hpp>
#include <engine/memory/QueuedOperations.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fmt/format.h>
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::memory;

RenderEntityCompiler::RenderEntityCompiler(std::shared_ptr<const ICore> core, std::shared_ptr<const vulkan::Device> device,
	std::shared_ptr<const vulkan::RenderPass> renderPass, std::shared_ptr<RenderManager> renderManager, uint32_t subpassNumber) :
	core_(core), device_(device), renderPass_(renderPass), renderManager_(renderManager), subpassNumber_(subpassNumber),
	worldManager_(renderManager_->getWorldManager()),
	memoryManager_(std::make_unique<MemoryManager>(device)),
	memoryHelper_(std::make_unique<MemoryHelper>(device)),
	commandPool_(std::make_shared<vulkan::CommandPool>(device_, 0))
{

}

uint32_t RenderEntityCompiler::getSubpassNumber() const
{
	return subpassNumber_;
}

std::shared_ptr<RenderEntityCompiler::RenderEntity> RenderEntityCompiler::createEntity(std::vector<EntityInfo> infos,
	const CubA4::object::RenderInfoComponent &render,
	const RenderFramebufferData &framebufferData)
{
	Data data {};
	constexpr const uint32_t TranformMatrixSize = sizeof(float) * 16;
	const size_t instanceCount = infos.size();
	commandPool_->allocate(1, &data.cmdBuffer, VK_COMMAND_BUFFER_LEVEL_SECONDARY);
	data.renderModel = std::dynamic_pointer_cast<const CubA4::render::engine::model::EntityRenderModel>(render.renderModel);

	createIntancesBuffer(data, instanceCount);

	for (size_t idx = 0; idx < infos.size(); ++idx)
	{
		auto &info = infos[idx];
		auto key = std::make_pair(info.factoryId, info.entityId);
		float *memory = reinterpret_cast<float*>(data.intanceHostMemory.get());
		memory += 16 * idx;
		data.transforms_.insert(std::make_pair(key, memory));
		updateTransforms(info.transform, memory);
	}


	data.memoryHost->flush(0, VK_WHOLE_SIZE);

	recordCmdBuffer(data, framebufferData);

	// TODO: maybe do it outside?
	memoryHelper_->copyBufferToBuffer(data.instanceHostBuffer->get(), data.instanceDeviceBuffer->get(), data.bufferSize).wait();


	std::function<void()> del = [cmdBuffer = data.cmdBuffer, pool = commandPool_]()
	{
		pool->free(1, &cmdBuffer);
	};

	return std::make_shared<RenderEntity>(data, del);
}

std::shared_ptr<RenderEntityCompiler::RenderEntity> RenderEntityCompiler::extendEntity(std::shared_ptr<RenderEntity> entity, std::vector<EntityInfo> infos,
	const CubA4::object::RenderInfoComponent &render, const RenderFramebufferData &framebufferData)
{
	Data data {};
	Data &oldData = entity->getData();
	constexpr const uint32_t TranformMatrixSize = sizeof(float) * 16;
	const size_t instanceCount = infos.size() + oldData.transforms_.size();
	commandPool_->allocate(1, &data.cmdBuffer, VK_COMMAND_BUFFER_LEVEL_SECONDARY);
	data.renderModel = std::dynamic_pointer_cast<const CubA4::render::engine::model::EntityRenderModel>(render.renderModel);

	createIntancesBuffer(data, instanceCount);
	memcpy(data.intanceHostMemory.get(), oldData.intanceHostMemory.get(), TranformMatrixSize * oldData.transforms_.size());

	for (size_t idx = 0; idx < oldData.transforms_.size(); ++idx)
	{
		float *memory = reinterpret_cast<float*>(data.intanceHostMemory.get());
		float *memoryOld = reinterpret_cast<float*>(oldData.intanceHostMemory.get());
		auto it = oldData.transforms_.begin();
		std::advance(it, idx);
		auto &key = it->first;
		auto *memoryOldWithOffset = it->second;
		auto offset = memoryOldWithOffset - memoryOld;
		memory += offset;
		data.transforms_.insert(std::make_pair(key, memory));
	}

	for (size_t idx = 0; idx < infos.size(); ++idx)
	{
		auto &info = infos[idx];
		auto key = std::make_pair(info.factoryId, info.entityId);
		float *memory = reinterpret_cast<float*>(data.intanceHostMemory.get());
		memory += 16 * (idx + oldData.transforms_.size());
		data.transforms_.insert(std::make_pair(key, memory));
		updateTransforms(info.transform, memory);
	}
	data.memoryHost->flush(0, VK_WHOLE_SIZE);

	recordCmdBuffer(data, framebufferData);

	// TODO: maybe do it outside?
	memoryHelper_->copyBufferToBuffer(data.instanceHostBuffer->get(), data.instanceDeviceBuffer->get(), data.bufferSize).wait();


	std::function<void()> del = [cmdBuffer = data.cmdBuffer, pool = commandPool_]()
	{
		pool->free(1, &cmdBuffer);
	};

	return std::make_shared<RenderEntity>(data, del);
}

std::shared_ptr<RenderEntityCompiler::RenderEntity> RenderEntityCompiler::shrinkEntity(RenderEntity &entity,
	std::vector<EntityInfo> infos, const CubA4::object::RenderInfoComponent &render, const RenderFramebufferData &framebufferData)
{
	Data data {};
	Data &oldData = entity.getData();

	constexpr const uint32_t TranformMatrixSize = sizeof(float) * 16;
	
	commandPool_->allocate(1, &data.cmdBuffer, VK_COMMAND_BUFFER_LEVEL_SECONDARY);
	data.renderModel = std::dynamic_pointer_cast<const CubA4::render::engine::model::EntityRenderModel>(render.renderModel);

	struct TempData
	{
		decltype(CubA4::object::WorldInfo::factoryId) factoryId;
		decltype(CubA4::object::WorldInfo::entityId) entityId;
		float matrix[16];
	};

	std::vector<TempData> infoCopy;
	infoCopy.reserve(oldData.transforms_.size());
	for (const auto [key, ptr] : oldData.transforms_)
	{
		TempData data
		{
			.factoryId = key.first,
			.entityId = key.second
		};
		memcpy(data.matrix, ptr, TranformMatrixSize);
		infoCopy.push_back(data);
	}

	auto removeIt = std::remove_if(infoCopy.begin(), infoCopy.end(), [&infos](const TempData &data)
	{
		return std::any_of(infos.begin(), infos.end(), [&data](const EntityInfo &info)
		{
			return info.factoryId == data.factoryId && info.entityId == data.entityId;
		});
	});

	infoCopy.erase(removeIt, infoCopy.end());

	const size_t instanceCount = infoCopy.size();
	createIntancesBuffer(data, instanceCount);

	for (size_t idx = 0; idx < infoCopy.size(); ++idx)
	{
		auto &info = infoCopy[idx];
		auto key = std::make_pair(info.factoryId, info.entityId);
		float *memory = reinterpret_cast<float*>(data.intanceHostMemory.get());
		memory += 16 * idx;
		data.transforms_.insert(std::make_pair(key, memory));
		memcpy(memory, info.matrix, TranformMatrixSize);
	}

	data.memoryHost->flush(0, VK_WHOLE_SIZE);

	// TODO: maybe do it outside?
	memoryHelper_->copyBufferToBuffer(data.instanceHostBuffer->get(), data.instanceDeviceBuffer->get(), data.bufferSize).wait();

	recordCmdBuffer(data, framebufferData);

	std::function<void()> del = [cmdBuffer = data.cmdBuffer, pool = commandPool_]()
	{
		pool->free(1, &cmdBuffer);
	};

	return std::make_shared<RenderEntity>(data, del);
}

void RenderEntityCompiler::updateEntity(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, RenderEntity &entity)
{
	auto key = std::make_pair(wi.factoryId, wi.entityId);
	auto &data = entity.getData();

	auto it = data.transforms_.find(key);
	if (it == data.transforms_.end())
		return;
	auto memory = it->second;

	updateTransforms(tr, memory);
	data.memoryHost->flush(0, VK_WHOLE_SIZE);

	VkBufferCopy region {
		.size = data.bufferSize
	};
	QueuedOperations::BufferToBufferCopy copyInfo {
		.src = data.instanceHostBuffer,
		.dst = data.instanceDeviceBuffer,
		.regions = {region},
		.bufferBarrierType = BufferBarrierType::Vertex
	};
	renderManager_->getResourceManager()->getQueuedOperations().queueCopyBufferToBuffer({copyInfo});

	// TODO: maybe do it outside?
	//memoryHelper_->copyBufferToBuffer(data.instanceHostBuffer->get(), data.instanceDeviceBuffer->get(), data.bufferSize).wait();
}

std::shared_ptr<RenderEntityCompiler::RenderEntity> RenderEntityCompiler::recompileEntity(std::shared_ptr<RenderEntity> entity,
	const RenderFramebufferData &framebufferData)
{
	Data data = entity->getData();
	commandPool_->allocate(1, &data.cmdBuffer, VK_COMMAND_BUFFER_LEVEL_SECONDARY);

	recordCmdBuffer(data, framebufferData);

	std::function<void()> del = [cmdBuffer = data.cmdBuffer, pool = commandPool_]()
	{
		pool->free(1, &cmdBuffer);
	};

	return std::make_shared<RenderEntity>(data, del);
}

void RenderEntityCompiler::recordCmdBuffer(Data &data, const RenderFramebufferData &framebufferData)
{
	const auto cmd = data.cmdBuffer;
	const uint32_t instanceCount = static_cast<uint32_t>(data.transforms_.size());

	VkCommandBufferInheritanceInfo inheritanceInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO,
		.renderPass = renderPass_->getRenderPass(),
		.subpass = subpassNumber_
	};
	VkCommandBufferBeginInfo beginInfo {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
		.pInheritanceInfo = &inheritanceInfo
	};

	
	VkRect2D scissor = {};
	scissor.extent.width = framebufferData.width;
	scissor.extent.height = framebufferData.height;

	VkViewport viewport = {};
	viewport.x = 0;
	viewport.y = 0;
	viewport.minDepth = 0;
	viewport.maxDepth = 1;
	viewport.width = static_cast<float>(scissor.extent.width);
	viewport.height = static_cast<float>(scissor.extent.height);

	auto renderMaterial = data.renderModel->getMaterial();
	auto worldSet = worldManager_->getWorldDescriptorSet();
	auto renderMaterialLayout = renderMaterial->getLayout();
	auto pipeline = renderMaterialLayout->getPipeline();

	constexpr const uint16_t descriptorSetCount = 1;
	VkDescriptorSet sets[descriptorSetCount] = { worldSet->get()};

	VkBuffer instanceDeviceBuffer = data.instanceDeviceBuffer->get();

	vkBeginCommandBuffer(cmd, &beginInfo);
	renderMaterial->apply(cmd);

	vkCmdSetViewport(cmd, 0, 1, &viewport);
	vkCmdSetScissor(cmd, 0, 1, &scissor);

	CubA4::world::ChunkPos chunkPos {};

	vkCmdPushConstants(cmd, pipeline->getLayout(), VK_SHADER_STAGE_ALL, 0, sizeof(chunkPos), &chunkPos);
	vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getLayout(), 0, descriptorSetCount, sets, 0, nullptr);
	
	data.renderModel->bind(cmd);
	static const VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(cmd, 1, 1, &instanceDeviceBuffer, &offset);

	auto labelText = fmt::format("Drawing entity {} with instance count of {}", data.renderModel->getId(), instanceCount);

	device_->getMarker().cmdLabelInsert(cmd, labelText, {0.f, 0.f, 0.5, 1.f});
	
	vkCmdDrawIndexed(cmd, data.renderModel->getIndexCount(), instanceCount, 0, 0, 0);

	vkEndCommandBuffer(cmd);
}

void RenderEntityCompiler::createIntancesBuffer(Data &data, size_t entityCount)
{
	data.bufferSize = entityCount * sizeof(float) * 16;

	VkBufferCreateInfo infoDevice {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = data.bufferSize,
		.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
	};
	VkBufferCreateInfo infoHost {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = data.bufferSize,
		.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
	};
	VkBuffer bufferDevice, bufferHost;
	if (vkCreateBuffer(device_->getDevice(), &infoDevice, nullptr, &bufferDevice) != VK_SUCCESS)
	{
		// TODO: logs, etc
		return;
	}
	if (vkCreateBuffer(device_->getDevice(), &infoHost, nullptr, &bufferHost) != VK_SUCCESS)
	{
		// TODO: logs, etc
		return;
	}

	device_->getMarker().setName(bufferDevice, "device buffer instance entity");
	device_->getMarker().setName(bufferHost, "host buffer instance entity");

	auto partDevice = memoryManager_->allocateAndBindPart(bufferDevice, MemoryAllocationPrefered::Device);
	auto partHost = memoryManager_->allocateAndBindPart(bufferHost, MemoryAllocationPrefered::Host);

	auto mappedMemory = partHost->map(0, VK_WHOLE_SIZE);

	auto delFunc = std::function([device = device_](VkBuffer buffer)
	{
		vkDestroyBuffer(device->getDevice(), buffer, nullptr);
	});

	data.instanceDeviceBuffer = CubA4::render::vulkan::util::createSharedVulkanObject(bufferDevice, delFunc);
	data.instanceHostBuffer = CubA4::render::vulkan::util::createSharedVulkanObject(bufferHost, delFunc);
	data.memoryDevice = partDevice;
	data.memoryHost = partHost;

	data.intanceHostMemory = mappedMemory;
}

void RenderEntityCompiler::updateTransforms(const CubA4::object::Transform &tr, float *mat4x4)
{
	auto globalPos = tr.position.globalPos<float>();
	glm::vec3 position {globalPos.x, globalPos.y, globalPos.z};
	glm::mat4x4 matrix(1.f);
	matrix = glm::translate(matrix, position);
	memcpy(mat4x4, glm::value_ptr(matrix), sizeof(float) * 16);
}