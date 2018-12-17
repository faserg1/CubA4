#include "./RenderChunkCompiler.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../../vulkan/RenderPass.hpp"
#include "../../vulkan/Pipeline.hpp"
#include "../world/RenderChunk.hpp"
#include <world/IChunk.hpp>
#include <object/IBlock.hpp>
#include "../model/RenderModel.hpp"
#include "../material/MaterialLayout.hpp"
#include "../material/Material.hpp"
#include "../world/WorldManager.hpp"
#include "../MemoryManager.hpp"
#include <algorithm>

using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

RenderChunkCompiler::RenderChunkCompiler(std::shared_ptr<const Device> device, std::shared_ptr<const RenderPass> renderPass, std::shared_ptr<const IWorldManager> worldManager) :
	RenderChunkCompilerCore(device), renderPass_(renderPass), worldManager_(std::dynamic_pointer_cast<const WorldManager>(worldManager))
{
}

RenderChunkCompiler::~RenderChunkCompiler()
{
}

std::future<std::shared_ptr<const RenderChunk>> RenderChunkCompiler::compileChunk(std::shared_ptr<const CubA4::mod::world::IChunk> chunk)
{
	return std::async(std::launch::async, &RenderChunkCompiler::compileChunkInternal, this, chunk);
}

std::shared_ptr<const RenderChunk> RenderChunkCompiler::compileChunkInternal(std::shared_ptr<const CubA4::mod::world::IChunk> chunk)
{
	auto poolWrapper = lockCommandPool();
	auto usedBlocks = chunk->getUsedBlocks();
	std::vector<VkCommandBuffer> buffers(usedBlocks.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = poolWrapper->getPool()->getPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(usedBlocks.size());
	vkAllocateCommandBuffers(device_->getDevice(), &allocInfo, buffers.data());

	VkCommandBufferInheritanceInfo inheritanceInfo = {};
	inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inheritanceInfo.renderPass = renderPass_->getRenderPass();
	// TODO: [OOKAMI] Set valid subpass
	inheritanceInfo.subpass = 0;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	beginInfo.pInheritanceInfo = &inheritanceInfo;

	auto chunkPos = chunk->getChunkPos();
	auto worldSet = worldManager_->getWorldDescriptorSetLayout();
	VkDescriptorSet sets[] = { worldSet->get() };
	std::vector<VkBuffer> instanceInfos;
	std::vector<std::shared_ptr<const CubA4::render::engine::IMemoryPart>> memoryParts;

	for (std::size_t idx = 0; idx < usedBlocks.size(); idx++)
	{
		auto usedBlock = usedBlocks[idx];
		auto cmdBuffer = buffers[idx];

		auto renderModel = std::dynamic_pointer_cast<const model::RenderModel>(usedBlock->getRenderModel());
		auto renderMaterial = std::dynamic_pointer_cast<const material::Material>(usedBlock->getRenderMaterial());
		auto renderMaterialLayout = renderMaterial->getLayout();
		auto pipeline = renderMaterialLayout->getPipeline();

		// TODO: [OOKAMI] Передать реальные данные

		VkRect2D scissor = {};
		scissor.extent.width = 1024;
		scissor.extent.height = 720;

		VkViewport viewport = {};
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.01;
		viewport.maxDepth = 16 * 32;
		viewport.width = scissor.extent.width;
		viewport.height = scissor.extent.height;

		auto blockChunkPositions = chunk->getChunkPositions(usedBlock);
		std::vector<CubA4::mod::world::BasePos<float>> positions(blockChunkPositions.size());
		std::transform(blockChunkPositions.begin(), blockChunkPositions.end(), positions.begin(), [](CubA4::mod::world::BlockInChunkPos &pos) -> CubA4::mod::world::BasePos<float>
		{
			return {static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z)};
		});
		const uint32_t blocksSize = static_cast<uint32_t>(positions.size()) * sizeof(CubA4::mod::world::BasePos<float>);
		
		VkBufferCreateInfo instanceBufferInfo = {};
		VkBuffer instanceInfo = {};
		instanceBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		instanceBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		instanceBufferInfo.size = blocksSize;
		auto resultInstanceBufferCreate = vkCreateBuffer(device_->getDevice(), &instanceBufferInfo, nullptr, &instanceInfo);
		if (resultInstanceBufferCreate != VK_SUCCESS)
		{
			// TODO: [OOKAMI] Exception, etc
			continue;
		}
		instanceInfos.push_back(instanceInfo);
		VkMemoryRequirements req;
		vkGetBufferMemoryRequirements(device_->getDevice(), instanceInfo, &req);

		auto part = memManager_->allocatePart(req.size, req.alignment, req.memoryTypeBits);
		vkBindBufferMemory(device_->getDevice(), instanceInfo, part->getMemory()->getMemory(), part->getOffset());
		memoryParts.push_back(part);

		if (blocksSize < 65536)
			memManager_->updateBuffer(positions.data(), instanceInfo, 0, blocksSize);
		else
		{
			//TODO: [OOKMAI] Написать копировалку
		}

		vkBeginCommandBuffer(cmdBuffer, &beginInfo);
		/////////////////////////////////////////////////
		pipeline->bind(cmdBuffer);

		vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
		vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);

		vkCmdPushConstants(cmdBuffer, pipeline->getLayout(), VK_SHADER_STAGE_ALL, 0, sizeof(chunkPos), &chunkPos);
		vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getLayout(), 0, 1, sets, 0, nullptr);
		
		renderModel->bind(cmdBuffer);
		const VkDeviceSize offset = 0;
		vkCmdBindVertexBuffers(cmdBuffer, 1, 1, &instanceInfo, &offset);
		
		vkCmdDrawIndexed(cmdBuffer,
			renderModel->getIndexCount(), static_cast<uint32_t>(blockChunkPositions.size()),
			0, 0, 0);
		/////////////////////////////////////////////////
		vkEndCommandBuffer(cmdBuffer);
	}

	std::function<void()> deleter = [dev = device_, neededPool = poolWrapper->getPool(), buffers, instanceInfos, memoryParts]()
	{
		for (auto instanceInfo : instanceInfos)
			vkDestroyBuffer(dev->getDevice(), instanceInfo, nullptr);
		decltype(poolWrapper) lock;
		do
		{
			lock = neededPool->tryLock();
		} while (!lock);
		vkFreeCommandBuffers(dev->getDevice(), lock->getPool()->getPool(), static_cast<uint32_t>(buffers.size()), buffers.data());
	};

	return std::make_shared<world::RenderChunk>(chunk->getChunkPos(), buffers, deleter);
}