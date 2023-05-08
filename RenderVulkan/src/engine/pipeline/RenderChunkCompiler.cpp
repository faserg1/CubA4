#include "./RenderChunkCompiler.hpp"
#include "../ResourceManager.hpp"
#include <vulkan/Device.hpp>
#include <vulkan/Memory.hpp>
#include <vulkan/RenderPass.hpp>
#include <vulkan/pipeline/Pipeline.hpp>
#include "../world/RenderChunk.hpp"
#include <world/IChunk.hpp>
#include <object/IBlock.hpp>
#include "../model/RenderModel.hpp"
#include "../material/MaterialLayout.hpp"
#include "../material/Material.hpp"
#include "../world/WorldManager.hpp"
#include "../memory/MemoryManager.hpp"
#include "../memory/MemoryHelper.hpp"
#include <engine/RenderManager.hpp>
#include <algorithm>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/map.hpp>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

RenderChunkCompiler::RenderChunkCompiler(std::shared_ptr<const ICore> core, std::shared_ptr<const Device> device, std::shared_ptr<const RenderPass> renderPass,
	std::shared_ptr<RenderManager> renderManager) :
	RenderChunkCompilerCore(core, device, renderManager->getModelManager()), renderPass_(renderPass), 
	resourceManager_(renderManager->getResourceManager()), worldManager_(std::dynamic_pointer_cast<const WorldManager>(renderManager->getWorldManager()))
{
}

RenderChunkCompiler::~RenderChunkCompiler()
{
}

std::shared_ptr<const RenderChunk> RenderChunkCompiler::compileChunk(std::shared_ptr<const CubA4::world::IChunk> chunk, const RenderChunkPipelineData &data)
{
	auto compiledBlockData = compileBlocks(chunk);
	if (compiledBlockData.empty())
		return {};
	return RenderChunkCompiler::compileChunkInternal(compiledBlockData, chunk->getChunkPos(), data);
}

std::shared_ptr<const world::RenderChunk> RenderChunkCompiler::compileChunk(std::shared_ptr<const world::RenderChunk> chunk, const RenderChunkPipelineData &data)
{
	return RenderChunkCompiler::compileChunkInternal(chunk->getBlockData(), chunk->getChunkPos(), data);
}

// TODO: [OOKAMI] Отрефакторить это всё! 

std::shared_ptr<const RenderChunk> RenderChunkCompiler::compileChunkInternal(const RenderModels &compiledBlockData, const CubA4::world::ChunkPos &chunkPos, const RenderChunkPipelineData &pipelineData)
{
	auto materials = compiledBlockData | ranges::views::keys | ranges::to<std::vector>;
	auto renderModels = compiledBlockData | ranges::views::values | ranges::to<std::vector>;
	auto poolWrapper = lockCommandPool();
	auto descriptorPool = getDescriptorPool(poolWrapper);

	std::vector<VkCommandBuffer> buffers(compiledBlockData.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = poolWrapper->getPool()->getPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(compiledBlockData.size());
	vkAllocateCommandBuffers(device_->getDevice(), &allocInfo, buffers.data());

	VkCommandBufferInheritanceInfo inheritanceInfo = {};
	inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inheritanceInfo.renderPass = renderPass_->getRenderPass();
	inheritanceInfo.subpass = pipelineData.subpass;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	beginInfo.pInheritanceInfo = &inheritanceInfo;

	auto worldSet = worldManager_->getWorldDescriptorSet();
	
	std::vector<VkBuffer> instanceInfos;
	std::vector<std::shared_ptr<const IMemoryPart>> memoryParts;

	for (std::size_t idx = 0; idx < compiledBlockData.size(); idx++)
	{
		auto renderMaterial = materials[idx];
		auto renderModel = renderModels[idx];
		auto cmdBuffer = buffers[idx];
		
		auto renderMaterialLayout = renderMaterial->getLayout();
		auto pipeline = renderMaterialLayout->getPipeline();

		VkRect2D scissor = {};
		scissor.extent.width = pipelineData.width;
		scissor.extent.height = pipelineData.height;

		VkViewport viewport = {};
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0;
		viewport.maxDepth = 1;
		viewport.width = static_cast<float>(scissor.extent.width);
		viewport.height = static_cast<float>(scissor.extent.height);

		constexpr const uint16_t descriptorSetCount = 1;
		VkDescriptorSet sets[descriptorSetCount] = { worldSet->get()};

		vkBeginCommandBuffer(cmdBuffer, &beginInfo);
		/////////////////////////////////////////////////
		renderMaterial->apply(cmdBuffer);

		vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
		vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);

		vkCmdPushConstants(cmdBuffer, pipeline->getLayout(), VK_SHADER_STAGE_ALL, 0, sizeof(chunkPos), &chunkPos);
		vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getLayout(), 0, descriptorSetCount, sets, 0, nullptr);
		
		renderModel->bind(cmdBuffer);
		
		vkCmdDrawIndexed(cmdBuffer,
			renderModel->getIndexCount(), 1,
			0, 0, 0);
		/////////////////////////////////////////////////
		vkEndCommandBuffer(cmdBuffer);
	}

	std::function<void()> deleter = [dev = device_, neededPool = poolWrapper->getPool(), dPool = descriptorPool, buffers, instanceInfos, memoryParts]()
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
	world::RenderChunk::Data data {
		.pos = chunkPos,
		.cmdBuffers = buffers,
		.compiledBlockData = compiledBlockData,
		.data = pipelineData
	};

	return std::make_shared<world::RenderChunk>(data, deleter);
}
