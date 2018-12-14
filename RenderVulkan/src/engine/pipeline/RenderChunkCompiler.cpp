#include "./RenderChunkCompiler.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/RenderPass.hpp"
#include "../../vulkan/Pipeline.hpp"
#include "../world/RenderChunk.hpp"
#include <world/IChunk.hpp>
#include <object/IBlock.hpp>
#include "../model/RenderModel.hpp"
#include "../material/MaterialLayout.hpp"
#include "../material/Material.hpp"

using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

RenderChunkCompiler::RenderChunkCompiler(std::shared_ptr<const Device> device, std::shared_ptr<const RenderPass> renderPass) :
	RenderChunkCompilerCore(device), renderPass_(renderPass)
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

	for (std::size_t idx = 0; idx < usedBlocks.size(); idx++)
	{
		auto usedBlock = usedBlocks[idx];
		auto cmdBuffer = buffers[idx];

		auto renderModel = std::dynamic_pointer_cast<const model::RenderModel>(usedBlock->getRenderModel());
		auto renderMaterial = std::dynamic_pointer_cast<const material::Material>(usedBlock->getRenderMaterial());
		auto renderMaterialLayout = renderMaterial->getLayout();
		auto pipeline = renderMaterialLayout->getPipeline();

		auto blockChunkPositions = chunk->getChunkPositions(usedBlock);

		vkBeginCommandBuffer(cmdBuffer, &beginInfo);
		renderModel->bind(cmdBuffer);
		pipeline->bind(cmdBuffer);
		vkCmdPushConstants(cmdBuffer, pipeline->getLayout(), VK_SHADER_STAGE_ALL, 0, sizeof(chunkPos), &chunkPos);
		
		vkCmdDrawIndexed(cmdBuffer,
			renderModel->getIndexCount(), static_cast<uint32_t>(blockChunkPositions.size()),
			0, 0, 0);
		vkEndCommandBuffer(cmdBuffer);
	}

	std::function<void()> deleter = [dev = device_, neededPool = poolWrapper->getPool(), buffers]()
	{
		decltype(poolWrapper) lock;
		do
		{
			lock = neededPool->tryLock();
		} while (!lock);
		vkFreeCommandBuffers(dev->getDevice(), lock->getPool()->getPool(), static_cast<uint32_t>(buffers.size()), buffers.data());
	};

	return std::make_shared<world::RenderChunk>(chunk->getChunkPos(), buffers, deleter);
}