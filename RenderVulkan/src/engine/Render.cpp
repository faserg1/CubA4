#include "./Render.hpp"
#include "./memory/MemoryAllocator.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Swapchain.hpp"
#include "../vulkan/Semaphore.hpp"
#include "../vulkan/RenderPass.hpp"
#include "../vulkan/RenderPassBuilder.hpp"

#include <vulkan/util/ConfigConverter.hpp>
#include <config/IRenderConfig.hpp>

#include <engine/pipeline/RenderEngineWorldPipeline.hpp>
#include "./world/RenderChunk.hpp"

#include <cstring>
#include <cfloat>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;

constexpr uint32_t queryTimestampCount = 4;

Render::Render(std::shared_ptr<const Device> device, std::shared_ptr<RenderPassManager> rpManager, std::shared_ptr<FramebufferManager> framebufferManager, std::shared_ptr<const config::IRenderConfig> config) :
	device_(device), renderPassManager_(rpManager), framebufferManager_(framebufferManager), config_(config),
	queryPool_(std::make_shared<QueryPool>(device, VK_QUERY_TYPE_TIMESTAMP, queryTimestampCount, VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT))
{
	// TODO: allocate query buffers in count of 4
	// record them immidiatly for timestamps, reset


	// another approuch:
	// allocate 1 sim command buffer?
	// allocate 1 query, do the separate cycle that will wait for this query infinitly and update two atomics values:
	// difference and prev timestamp
}

Render::~Render()
{
	vkQueueWaitIdle(device_->getQueue()->get());
}

void Render::addSubPipeline(std::unique_ptr<ISubRenderPipeline> &&subPipeline)
{
	subPipelines_.emplace_back(std::make_pair(std::move(subPipeline), 0));
	std::sort(subPipelines_.begin(), subPipelines_.end(), [](auto &a, auto &b) -> bool
	{
		return a.first->getSubpass() < b.first->getSubpass();
	});
}

void Render::shutdown()
{
	subPipelines_.clear();
}

void Render::onAcquireFailed(std::shared_ptr<const vulkan::Semaphore> awaitSemaphore)
{
	//send command buffer to queue
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	std::vector<VkSemaphore> waitSemaphores = { awaitSemaphore->getSemaphore() };
	std::vector<VkPipelineStageFlags> waitFlags = { VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT };

	submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
	submitInfo.pWaitSemaphores = waitSemaphores.data();
	submitInfo.pWaitDstStageMask = waitFlags.data();

	auto q = device_->getQueue();
	vkQueueSubmit(q->get(), 1, &submitInfo, VK_NULL_HANDLE );
	onIterate();
}

void Render::onAcquire(uint32_t imgIndex)
{
	if (imgIndex != 0)
		return;
	onIterate();
}

void Render::record(std::shared_ptr<vulkan::Framebuffer> framebuffer, uint32_t imgIndex)
{
	if (!framebuffer->isRecordAwait())
		return;

	if (!framebuffer->waitFence())
		return;
	framebuffer->resetFence();

	auto vkCmdBuffer = framebuffer->getCommandBuffer();
	auto vkFramebuffer = framebuffer->getFrameBuffer();

	auto &mainInfo = renderPassManager_->getMainInfo();

	VkCommandBufferBeginInfo cmdBeginInfo = {};
	cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = vkFramebuffer;
	renderPassBeginInfo.renderPass = renderPassManager_->getMainRenderPass()->getRenderPass();

	VkClearValue colorAttachmentClearValue = {
		.color = {
			.float32 = { 0.2f, 0.3f,0.4f,0.f }
		}
	};
	//colorAttachmentClearValue.color.float32 = { 0.2f, 0.3f,0.4f,0.f };
	//memcpy(colorAttachmentClearValue.color.float32, clrClearFloat, sizeof(float) * 4);

	VkClearValue depthAttachmentsClearValue = {};
	depthAttachmentsClearValue.depthStencil.depth = 1.f;
	

	std::vector<VkClearValue> clearValues = 
	{
		colorAttachmentClearValue,
		depthAttachmentsClearValue
	};
	renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassBeginInfo.pClearValues = clearValues.data();

	renderPassBeginInfo.renderArea.extent = framebufferManager_->getExtent();

	vkBeginCommandBuffer(vkCmdBuffer, &cmdBeginInfo);
	vkCmdBeginRenderPass(vkCmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);

	uint32_t currentSubpass = 0;

	////////////////////////////////////////////////////////////

	for (auto &subPipeline : subPipelines_)
	{
		device_->getMarker().cmdLabelBegin(vkCmdBuffer, subPipeline.first->debugName(), subPipeline.first->debugColor());
		while (subPipeline.first->getSubpass() > currentSubpass)
		{
			++currentSubpass;
			vkCmdNextSubpass(vkCmdBuffer, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
		}
		subPipeline.first->executeFrom(vkCmdBuffer);
		if (subPipeline.first->getVersion() > subPipeline.second)
			subPipeline.second++;
		device_->getMarker().cmdLabelEnd(vkCmdBuffer);
	}

	
	////////////////////////////////////////////////////////////
	vkCmdEndRenderPass(vkCmdBuffer);
	vkEndCommandBuffer(vkCmdBuffer);
	framebuffer->onRecorded();
}

std::shared_ptr<const Semaphore> Render::send(std::shared_ptr<vulkan::Framebuffer> framebuffer, std::shared_ptr<const Semaphore> awaitSemaphore)
{
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

	return renderDoneSemaphore;
}

std::shared_ptr<const CubA4::render::config::IRenderConfig> Render::getConfig() const
{
	return config_;
}

void Render::onIterate()
{
	bool isDirty = false;
	for (auto &subPipeline : subPipelines_)
	{
		subPipeline.first->onIterate();
		auto version = subPipeline.first->getVersion();
		if (version != subPipeline.second)
			isDirty = true;
	}
	if (isDirty)
		framebufferManager_->markDirty();
}