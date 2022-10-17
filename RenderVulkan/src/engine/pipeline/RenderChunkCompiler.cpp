#include "./RenderChunkCompiler.hpp"
#include "../ResourceManager.hpp"
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../../vulkan/RenderPass.hpp"
#include "../../vulkan/Pipeline.hpp"
#include "../world/RenderChunk.hpp"
#include <world/IChunk.hpp>
#include <world/IChunkRange.hpp>
#include <object/IBlock.hpp>
#include "../model/RenderModel.hpp"
#include "../material/MaterialLayout.hpp"
#include "../material/Material.hpp"
#include "../world/WorldManager.hpp"
#include "../memory/MemoryManager.hpp"
#include "../memory/MemoryHelper.hpp"
#include <algorithm>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

RenderChunkCompiler::RenderChunkCompiler(std::shared_ptr<const Device> device, std::shared_ptr<const RenderPass> renderPass,
	std::shared_ptr<ResourceManager> resourceManager, std::shared_ptr<const IWorldManager> worldManager) :
	RenderChunkCompilerCore(device), renderPass_(renderPass), 
	resourceManager_(resourceManager), worldManager_(std::dynamic_pointer_cast<const WorldManager>(worldManager))
{
}

RenderChunkCompiler::~RenderChunkCompiler()
{
}

std::future<std::shared_ptr<const RenderChunk>> RenderChunkCompiler::compileChunk(std::shared_ptr<const CubA4::mod::world::IChunk> chunk)
{
	return std::async(std::launch::async, &RenderChunkCompiler::compileChunkInternal, this, chunk);
}

// TODO: [OOKAMI] Отрефакторить это всё! 

std::shared_ptr<const RenderChunk> RenderChunkCompiler::compileChunkInternal(std::shared_ptr<const CubA4::mod::world::IChunk> chunk)
{
	auto poolWrapper = lockCommandPool();
	auto descriptorPool = getDescriptorPool(poolWrapper);

	auto worldLayoutSet = resourceManager_->getWorldLayout();
	auto chunkLayoutSet = resourceManager_->getChunkLayout();

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
	auto worldSet = worldManager_->getWorldDescriptorSet();
	
	std::vector<VkBuffer> instanceInfos;
	std::vector<std::shared_ptr<const IMemoryPart>> memoryParts;

	VkDescriptorSet chunkRangeDescriptorSet = VK_NULL_HANDLE;

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
		viewport.minDepth = 0;
		viewport.maxDepth = 1;
		viewport.width = static_cast<float>(scissor.extent.width);
		viewport.height = static_cast<float>(scissor.extent.height);

		auto chunkRanges = chunk->getChunkRanges(usedBlock);
		uint32_t chunkRangesCount = static_cast<uint32_t>(chunkRanges.size());
		uint32_t instanceCount = 0;
		std::vector<CubA4::core::world::BasePos<uint32_t>> totalRangeBounds;
		totalRangeBounds.reserve(chunkRangesCount * CubA4::mod::world::BoundsSize);

		for (auto chunkRange : chunkRanges)
		{
			instanceCount += chunkRange->getBlockCount();
			auto rangeBounds = chunkRange->getBounds();
			for (auto rangeBound : rangeBounds)
				totalRangeBounds.push_back(CubA4::core::world::convertPos<uint32_t>(rangeBound));
		}

		VkBuffer totalRangeBuffer;
		std::shared_ptr<const IMemoryPart> totalRangeMemoryPart;

		const auto dataSize = totalRangeBounds.size() * sizeof(decltype(*totalRangeBounds.data()));
		std::tie(totalRangeBuffer, totalRangeMemoryPart) = createBufferFromData(totalRangeBounds.data(), dataSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		const auto dType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		chunkRangeDescriptorSet = prepareSetWithBuffer(descriptorPool->get(), chunkLayoutSet->get(), totalRangeBuffer, dType, 1);

		instanceInfos.push_back(totalRangeBuffer);
		memoryParts.push_back(totalRangeMemoryPart);

		constexpr const uint16_t descriptorSetCount = 3;
		VkDescriptorSet sets[descriptorSetCount] = { worldSet->get(), chunkRangeDescriptorSet, renderMaterial->getDescriptorSet()};

		vkBeginCommandBuffer(cmdBuffer, &beginInfo);
		/////////////////////////////////////////////////
		pipeline->bind(cmdBuffer);

		vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
		vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);

		vkCmdPushConstants(cmdBuffer, pipeline->getLayout(), VK_SHADER_STAGE_ALL, 0, sizeof(chunkPos), &chunkPos);
		vkCmdPushConstants(cmdBuffer, pipeline->getLayout(), VK_SHADER_STAGE_ALL, sizeof(chunkPos), sizeof(uint32_t), &chunkRangesCount);
		vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getLayout(), 0, descriptorSetCount, sets, 0, nullptr);
		
		renderModel->bind(cmdBuffer);
		
		vkCmdDrawIndexed(cmdBuffer,
			renderModel->getIndexCount(), instanceCount,
			0, 0, 0);
		/////////////////////////////////////////////////
		vkEndCommandBuffer(cmdBuffer);
	}

	std::function<void()> deleter = [dev = device_, neededPool = poolWrapper->getPool(), dPool = descriptorPool, chunkRangeDescriptorSet, buffers, instanceInfos, memoryParts]()
	{
		vkFreeDescriptorSets(dev->getDevice(), dPool->get(), 1, &chunkRangeDescriptorSet);

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

std::tuple<VkBuffer, std::shared_ptr<const IMemoryPart>> RenderChunkCompiler::createBufferFromData(void *data, size_t size, VkBufferUsageFlags flags) const
{
	VkBufferCreateInfo bufferInfo = {};
	VkBuffer instanceInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | flags;
	bufferInfo.size = size;
	auto result = vkCreateBuffer(device_->getDevice(), &bufferInfo, nullptr, &instanceInfo);
	if (result != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return { VK_NULL_HANDLE, {} };
	}

	MemoryHelper helper(device_);

	VkMemoryRequirements req;
	vkGetBufferMemoryRequirements(device_->getDevice(), instanceInfo, &req);

	auto part = memManager_->allocatePart(req.size, req.alignment, req.memoryTypeBits);
	result = vkBindBufferMemory(device_->getDevice(), instanceInfo, part->getMemory()->getMemory(), part->getOffset());
	if (result != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return { VK_NULL_HANDLE, {} };
	}

	// TODO: [OOKAMI] Переместить максимальный размер для обновления буфера в константы... Или убрать всё этопод капот... Или просто запретить делать такие объемы данных
	if (size < 65536)
		helper.updateBuffer(data, instanceInfo, 0, size);
	else
	{
		//TODO: [OOKMAI] Написать копировалку
	}

	return {instanceInfo, part};
}

VkDescriptorSet RenderChunkCompiler::prepareSetWithBuffer(VkDescriptorPool pool, VkDescriptorSetLayout layout, VkBuffer buffer, VkDescriptorType type, uint32_t binding) const
{
	VkDescriptorSetLayout layouts[] = { layout };

	VkDescriptorSetAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	info.descriptorPool = pool;
	info.descriptorSetCount = 1;
	info.pSetLayouts = layouts;

	VkDescriptorSet set = {};

	vkAllocateDescriptorSets(device_->getDevice(), &info, &set);

	VkDescriptorBufferInfo bufferWriteInfo = {};
	bufferWriteInfo.buffer = buffer;
	bufferWriteInfo.range = VK_WHOLE_SIZE;

	VkWriteDescriptorSet writeSet = {};
	writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeSet.dstSet = set;
	writeSet.dstBinding = binding;
	writeSet.descriptorType = type;
	writeSet.pBufferInfo = &bufferWriteInfo;
	writeSet.descriptorCount = 1;
	vkUpdateDescriptorSets(device_->getDevice(), 1, &writeSet, 0, nullptr);

	return set;
}