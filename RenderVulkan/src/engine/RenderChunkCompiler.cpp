#include "./RenderChunkCompiler.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/RenderPass.hpp"
#include "world/RenderChunk.hpp"
#include <world/IChunk.hpp>
#include <object/IBlock.hpp>
#include "model/RenderModel.hpp"
#include "material/MaterialLayout.hpp"
#include "material/Material.hpp"
#include "../vulkan/Pipeline.hpp"

using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

RenderChunkCompiler::RenderChunkCompiler(std::shared_ptr<const Device> device, std::shared_ptr<const RenderPass> renderPass) :
	RenderChunkCompilerCore(device), renderPass_(renderPass)
{
}

RenderChunkCompiler::~RenderChunkCompiler()
{
}

std::shared_future<std::shared_ptr<const world::RenderChunk>> RenderChunkCompiler::compileChunk(std::shared_ptr<CubA4::mod::world::IChunk> chunk)
{
	return std::async(std::launch::async, &RenderChunkCompiler::compileChunkInternal, this, chunk).share();
}

std::shared_ptr<const world::RenderChunk> RenderChunkCompiler::compileChunkInternal(std::shared_ptr<CubA4::mod::world::IChunk> chunk)
{
	auto poolWrapper = lockCommandPool();
	auto usedBlocks = chunk->getUsedBlocks();
	std::vector<VkCommandBuffer> buffers(usedBlocks.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = poolWrapper->vkPool;
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
		
		vkCmdDrawIndexed(cmdBuffer,
			renderModel->getIndexCount(), static_cast<uint32_t>(blockChunkPositions.size()),
			0, 0, 0);
		vkEndCommandBuffer(cmdBuffer);
	}
	return std::make_shared<world::RenderChunk>();
}