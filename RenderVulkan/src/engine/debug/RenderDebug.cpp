#include <engine/debug/RenderDebug.hpp>
#include <engine/ResourceManager.hpp>
#include <vulkan/pipeline/PipelineBuilderLine.hpp>
#include <vulkan/pipeline/PipelineBuilderWireframe.hpp>
#include <engine/material/IShader.hpp>
#include <irs.hpp>
using namespace CubA4::render::engine::debug;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::vulkan;

RenderDebug::RenderDebug(std::shared_ptr<const vulkan::Device> device,
	std::shared_ptr<const RenderPassManager> rpManager,
	std::shared_ptr<CubA4::render::engine::ResourceManager> resManager,
	std::shared_ptr<const CubA4::render::engine::world::WorldManager> worldManager,
	CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), rpManager_(rpManager), resManager_(resManager), worldManager_(worldManager),
	config_(config),
	framebufferManager_(std::make_unique<DebugFramebufferManager>(device, config)),
	memoryManager_(std::make_shared<MemoryManager>(device)),
	memoryHelper_(std::make_shared<MemoryHelper>(device)),
	shaderFactory_(device), cmdPool_(device, 0)
{
}

std::shared_ptr<IRenderDebugCollection> RenderDebug::addCollection()
{
	auto collection = std::make_shared<RenderDebugCollection>(
		cmdPool_, rpManager_->getDebugRenderPass(), shared_from_this());
	collections_.push_back(collection);
	return collection;
}

void RenderDebug::setEnabled(bool enabled)
{
	enabled_ = enabled;
}

bool RenderDebug::isEnabled() const
{
	return enabled_;
}

void RenderDebug::swapchainChanged(std::shared_ptr<const Swapchain> swapchain, std::vector<VkImage> mainDepths)
{
	framebufferManager_->setMainDepths(std::move(mainDepths));
	framebufferManager_->onSwapchainUpdate(swapchain);
}

void RenderDebug::onRenderPassCreated()
{
	framebufferManager_->setRenderPass(rpManager_->getDebugRenderPass());
}

void RenderDebug::setup()
{
	createPipelines();
}

std::shared_ptr<const Semaphore> RenderDebug::render(uint32_t frame, std::shared_ptr<const Semaphore> awaitSemaphore)
{
	record(frame);
	auto renderDoneSemapore = framebufferManager_->get(frame)->getRenderDoneSemaphore();
	send(frame, awaitSemaphore);
	return renderDoneSemapore;
}

void RenderDebug::record(uint32_t frame)
{
	auto framebuffer = framebufferManager_->onAcquire(frame);

	if (!framebuffer->isRecordAwait())
		return;

	if (!framebuffer->waitFence())
		return;
		
	framebuffer->resetFence();

	auto vkCmdBuffer = framebuffer->getCommandBuffer();
	auto vkFramebuffer = framebuffer->getFrameBuffer();

	auto depthIdx = std::numeric_limits<uint32_t>::max();
	for (uint32_t aIdx = 0; aIdx < framebuffer->getAttachmentsCount(); aIdx++)
	{
		const auto &attachment = framebuffer->getFrameBufferImage(aIdx);
		if (attachment.getAspectFlags() == VK_IMAGE_ASPECT_DEPTH_BIT)
		{
			depthIdx = aIdx;
			break;
		}
	}

	const auto &attachment = framebuffer->getFrameBufferImage(depthIdx);
	const auto dstDepthImage = attachment.getImage();

	VkCommandBufferBeginInfo cmdBeginInfo = {};
	cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = vkFramebuffer;
	renderPassBeginInfo.renderPass = rpManager_->getDebugRenderPass()->getRenderPass();

	renderPassBeginInfo.renderArea.extent = framebufferManager_->getExtent();

	vkBeginCommandBuffer(vkCmdBuffer, &cmdBeginInfo);

	vkCmdBeginRenderPass(vkCmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	device_->getMarker().cmdLabelInsert(vkCmdBuffer, "Depth resolve", {0.f, 1.f, 0.f, 0.5});

	vkCmdNextSubpass(vkCmdBuffer, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);

	std::vector<decltype(collections_)::iterator> toRemove;
	for (auto it = collections_.begin(); it != collections_.end(); it++)
	{
		if (it->expired())
		{
			toRemove.push_back(it);
			continue;
		}
		auto collection = it->lock();
		collection->record(vkCmdBuffer, rpManager_->getDebugInfo().debugSubpass, framebufferManager_->getExtent());
	}

	vkCmdEndRenderPass(vkCmdBuffer);
	vkEndCommandBuffer(vkCmdBuffer);

	for (auto toRemoveIt : toRemove)
	{
		collections_.erase(toRemoveIt);
	}

	framebuffer->onRecorded();
}

void RenderDebug::send(uint32_t frame, std::shared_ptr<const Semaphore> awaitSemaphore)
{
	auto framebuffer = framebufferManager_->get(frame);
	auto vkCmdBuffer = framebuffer->getCommandBuffer();
	auto renderDoneSemaphore = framebuffer->getRenderDoneSemaphore();

	//send command buffer to queue
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	if (framebuffer->isRecorded())
	{
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &vkCmdBuffer;
	}
	
	std::vector<VkSemaphore> signalSemaphores = { renderDoneSemaphore->getSemaphore() };
	std::vector<VkSemaphore> waitSemaphores = { awaitSemaphore->getSemaphore() };
	std::vector<VkPipelineStageFlags> waitFlags = { VK_PIPELINE_STAGE_ALL_COMMANDS_BIT };

	submitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
	submitInfo.pSignalSemaphores = signalSemaphores.data();

	submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
	submitInfo.pWaitSemaphores = waitSemaphores.data();
	submitInfo.pWaitDstStageMask = waitFlags.data();

	auto q = device_->getQueue();
	vkQueueSubmit(q->get(), 1, &submitInfo, framebuffer->isDirty() ? framebuffer->getFence() : VK_NULL_HANDLE);
	if (framebuffer->isDirty())
		framebuffer->onRecordAwait();
}

void RenderDebug::onCommandsDirty()
{
	framebufferManager_->markDirty();
}

std::shared_ptr<CubA4::render::vulkan::Pipeline> RenderDebug::getPipeline(PipelineType type) const
{
	switch (type)
	{
	case PipelineType::Line:
		return line_;
	case PipelineType::Wireframe:
		return wireframe_;
	}
	return {};
}

void RenderDebug::createPipelines()
{
	PipelineBuilderLine linePipelineBuilder(device_, config_);
	PipelineBuilderWireframe wireframePipelineBuilder(device_, config_);

	linePipelineBuilder.addBuiltInDescriptorSetLayouts(resManager_->getBuiltInLayouts());
	wireframePipelineBuilder.addBuiltInDescriptorSetLayouts(resManager_->getBuiltInLayouts());

	// useShaders

	{
		std::shared_ptr<const engine::material::IShader> vertexShader, fragmentShader;

		const void *vertexShaderData, *fragmentShaderData;
		std::size_t vertexShaderSize, fragmentShaderSize;

		vertexShaderData = irs::findFile("shaders/debug.vert.spv", vertexShaderSize);
		fragmentShaderData = irs::findFile("shaders/debug.frag.spv", fragmentShaderSize);

		if (!vertexShaderData || !fragmentShaderData)
		{
			// TODO: [OOKAMI] Logs, exceptions...
			return;
		}

		vertexShader = shaderFactory_.createFromBinary(vertexShaderData, vertexShaderSize, CubA4::render::engine::material::ShaderType::Vertex, "main");
		fragmentShader = shaderFactory_.createFromBinary(fragmentShaderData, fragmentShaderSize, CubA4::render::engine::material::ShaderType::Fragment, "main");

		linePipelineBuilder.useShader(vertexShader);
		wireframePipelineBuilder.useShader(vertexShader);
		linePipelineBuilder.useShader(fragmentShader);
		wireframePipelineBuilder.useShader(fragmentShader);
	}

	std::vector<VkGraphicsPipelineCreateInfo> pipelineCreateInfos(2);
	std::vector<VkPipeline> pipelines(2);
	pipelineCreateInfos[0] = linePipelineBuilder.build();
	pipelineCreateInfos[1] = wireframePipelineBuilder.build();

	for (auto &createInfo : pipelineCreateInfos)
	{
		createInfo.renderPass = rpManager_->getDebugRenderPass()->getRenderPass();
		createInfo.subpass = rpManager_->getDebugInfo().debugSubpass;
	}
		

	if (vkCreateGraphicsPipelines(device_->getDevice(), VK_NULL_HANDLE,
		static_cast<uint32_t>(pipelineCreateInfos.size()), pipelineCreateInfos.data(), nullptr, pipelines.data()) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}

	vulkan::PipelineInfo info;
	
	linePipelineBuilder.fillPipelineInfo(info);
	info.pipeline = pipelines[0];
	line_ = std::make_shared<vulkan::Pipeline>(device_, info);

	wireframePipelineBuilder.fillPipelineInfo(info);
	info.pipeline = pipelines[1];
	wireframe_ = std::make_shared<vulkan::Pipeline>(device_, info);
}

DebugRenderModel RenderDebug::createBuffer(std::vector<VertexColor> vertices)
{
	// TODO: move to template class?

	VkBuffer vertexBuffer, vertexTransitBuffer;

	uint64_t verticesSize = ///< Размер буфера вершин, в байтах
		vertices.size() * sizeof(VertexColor); 

	const unsigned char bufferCount = 2;
	VkBufferCreateInfo bufferInfos[bufferCount] = {};
	for (unsigned char bufferIndex = 0; bufferIndex < bufferCount; bufferIndex++)
	{
		bufferInfos[bufferIndex].sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfos[bufferIndex].sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}


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

	auto memoryVertexTransitBufferPart = memoryManager_->allocatePart(
		reqVertexTransitBuffer.memoryRequirements.size, reqVertexTransitBuffer.memoryRequirements.alignment,
		reqVertexTransitBuffer.memoryRequirements.memoryTypeBits, MemoryAllocationPrefered::Host);
	auto memoryVertexBufferPart = memoryManager_->allocatePart(
		reqVertexBuffer.memoryRequirements.size, reqVertexBuffer.memoryRequirements.alignment,
		reqVertexBuffer.memoryRequirements.memoryTypeBits, MemoryAllocationPrefered::Device);

	/// Fill the vertex buffer
	auto mappedVertexMemory = memoryVertexTransitBufferPart->map(0, VK_WHOLE_SIZE);
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
	}
	mappedVertexMemory.reset();

	// Bind and copy

	vkBindBufferMemory(device_->getDevice(), vertexTransitBuffer,
		memoryVertexTransitBufferPart->getMemory()->getMemory(), memoryVertexTransitBufferPart->getOffset());
	vkBindBufferMemory(device_->getDevice(), vertexBuffer, memoryVertexBufferPart->getMemory()->getMemory(), memoryVertexBufferPart->getOffset());

	memoryHelper_->copyBufferToBuffer(vertexTransitBuffer, vertexBuffer, verticesSize).wait();

	vkDestroyBuffer(device_->getDevice(), vertexTransitBuffer, nullptr);

	const auto deleter = std::function([device = device_](VkBuffer buffer)
	{
		vkDestroyBuffer(device->getDevice(), buffer, nullptr);
	});

	return DebugRenderModel {
		.memoryPart = memoryVertexBufferPart,
		.vertexBuffer = CubA4::render::vulkan::util::createSharedVulkanObject(vertexBuffer, deleter),
		.vertexCount = static_cast<uint32_t>(vertices.size())
	};
}

sVkDescriptorSet RenderDebug::getWorldDescriptorSet()
{
	return worldManager_->getWorldDescriptorSet();
}