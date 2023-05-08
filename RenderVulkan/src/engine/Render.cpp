#include "./Render.hpp"
#include "./memory/MemoryAllocator.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Swapchain.hpp"
#include "../vulkan/Semaphore.hpp"
#include "../vulkan/RenderPass.hpp"
#include "../vulkan/RenderPassBuilder.hpp"

#include "./pipeline/RenderEnginePipeline.hpp"
#include "./world/RenderChunk.hpp"

#include <cstring>
#include <cfloat>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;

Render::Render(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain) :
	device_(device), swapchain_(swapchain), framebuffersBuilder_(device_)
{
	createRenderPass();
	createFramebuffers();
}

Render::~Render()
{
	vkQueueWaitIdle(device_->getQueue()->get());
	destroyFramebuffers();
	destroyRenderPass();
}

void Render::setup(std::shared_ptr<RenderEnginePipeline> pipeline)
{
	chunkUpdateSubscription_ = pipeline->subscribe(this);
}

void Render::shutdown()
{
	chunkUpdateSubscription_->unsubscribe();
}

void Render::swapchainChanged(std::shared_ptr<const vulkan::Swapchain> swapchain)
{
	oldFramebuffers_.push_back(OldFramebufferInfo {
		.cyclesLeft = 10,
		.oldSwapchain = swapchain_,
		.oldFramebuffers = framebuffers_,
	});
	swapchain_ = swapchain;
	createFramebuffers();
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
	onCycle();
}

std::shared_ptr<Framebuffer> Render::onAcquire(uint32_t imgIndex)
{
	if (imgIndex == 0)
		onCycle();
	framebuffers_[imgIndex]->onAquired();
	return framebuffers_[imgIndex];
}

void Render::record(std::shared_ptr<vulkan::Framebuffer> framebuffer)
{
	if (!framebuffer->isRecordAwait())
		return;

	if (!framebuffer->waitFence())
		return;
	framebuffer->resetFence();

	auto vkCmdBuffer = framebuffer->getCommandBuffer();
	auto vkFramebuffer = framebuffer->getFrameBuffer();

	VkCommandBufferBeginInfo cmdBeginInfo = {};
	cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = vkFramebuffer;
	renderPassBeginInfo.renderPass = renderPass_->getRenderPass();

	VkClearValue colorAttachmentClearValue = {};
	float clrClearFloat[4] = { 0.2f,0.3f,0.4f,0.f };
	memcpy(colorAttachmentClearValue.color.float32, clrClearFloat, sizeof(float) * 4);

	VkClearValue depthAttachmentsClearValue = {};
	depthAttachmentsClearValue.depthStencil.depth = 1.f;
	

	std::vector<VkClearValue> clearValues = 
	{
		colorAttachmentClearValue,
		depthAttachmentsClearValue
	};
	renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassBeginInfo.pClearValues = clearValues.data();

	renderPassBeginInfo.renderArea.extent = swapchain_->getResolution();

	vkBeginCommandBuffer(vkCmdBuffer, &cmdBeginInfo);
	vkCmdBeginRenderPass(vkCmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	////////////////////////////////////////////////////////////
	decltype(chunks_) chunks;

	{
		auto locker = chunkLock_.lock();
		chunks = chunks_;
	}

	for (auto chunk : chunks)
	{
		if (!chunk)
			continue;
		chunk->executeFrom(vkCmdBuffer);
	}
	////////////////////////////////////////////////////////////
	vkCmdEndRenderPass(vkCmdBuffer);

	if (false)
	{
		VkResolveImageInfo2 resolveImageInfo;
		resolveImageInfo.sType = VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2;
		resolveImageInfo.srcImage = framebuffer->getFramebufferImage();
		resolveImageInfo.dstImage = framebuffer->getPresentImage();
		resolveImageInfo.srcImageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		resolveImageInfo.dstImageLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		vkCmdResolveImage2(vkCmdBuffer, &resolveImageInfo);
	}
	

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

std::shared_ptr<const RenderPass> Render::getRenderPass() const
{
	return renderPass_;
}

void Render::createRenderPass()
{
	RenderPassBuilder builder(device_, swapchain_);
	renderPass_ = builder.build();
}

void Render::destroyRenderPass()
{
	renderPass_.reset();
}

void Render::createFramebuffers()
{
	framebuffers_ = framebuffersBuilder_.createFramebuffers(swapchain_, renderPass_);
}

void Render::destroyFramebuffers()
{
	framebuffers_.clear();
}

void Render::onCycle()
{
	auto locker = oldFramebuffersLock_.lock();
	auto it = std::remove_if(oldFramebuffers_.begin(), oldFramebuffers_.end(), [](OldFramebufferInfo &oldInfo) -> bool
	{
		if (oldInfo.cyclesLeft > 0)
			oldInfo.cyclesLeft--;
		return !oldInfo.cyclesLeft;
	});
	oldFramebuffers_.erase(it, oldFramebuffers_.end());
}

void Render::chunksUpdated(std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> renderChunks)
{
	{
		auto locker = chunkLock_.lock();
		auto locker2 = oldFramebuffersLock_.lock();
		oldFramebuffers_.push_back(OldFramebufferInfo {
			.cyclesLeft = 10,
			.oldChunks = chunks_
		});
		chunks_ = renderChunks;
	}
	for (auto &framebuffer : framebuffers_)
	{
		framebuffer->markDirty();
	}
}