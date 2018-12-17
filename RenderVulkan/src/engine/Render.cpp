#include "./Render.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Swapchain.hpp"
#include "../vulkan/Semaphore.hpp"
#include "../vulkan/RenderPass.hpp"
#include "../vulkan/RenderPassBuilder.hpp"

#include "./pipeline/RenderEnginePipeline.hpp"
#include "./world/RenderChunk.hpp"

#include <cstring>

using namespace CubA4::render::engine;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::render::vulkan;

Render::Render(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain) :
	device_(device), swapchain_(swapchain), chunksLocked_(false)
{
	createMainCommandPool();
	createRenderPass();
	createFramebuffers();
}

Render::~Render()
{
	vkQueueWaitIdle(device_->getQueue()->get());
	destroyFramebuffers();
	destroyRenderPass();
	destroyMainCommandPool();
}

Render::FramebufferData::FramebufferData() :
	dirty(true), needUpdate(false), recorded(false)
{
}

Render::FramebufferData::FramebufferData(const FramebufferData &) :
	dirty(true), needUpdate(false), recorded(false)
{
}

void Render::setup(std::shared_ptr<RenderEnginePipeline> pipeline)
{
	chunkUpdateSubscription_ = pipeline->subscribe(this);
}

void Render::shutdown()
{
	chunkUpdateSubscription_->unsubscribe();
}

void Render::record(uint32_t imgIndex)
{
	if (!framebuffersData_[imgIndex].needUpdate && framebuffersData_[imgIndex].recorded)
		return;

	auto cmdBuffer = framebuffersData_[imgIndex].cmdBuffer;
	auto framebuffer = framebuffersData_[imgIndex].framebuffer;
	auto fence = framebuffersData_[imgIndex].fence;

	VkCommandBufferBeginInfo cmdBeginInfo = {};
	cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = framebuffer;
	renderPassBeginInfo.renderPass = renderPass_->getRenderPass();

	VkClearValue colorAttachmentClearValue = {};
	float clrClearFloat[4] = { 0.2f,0.3f,0.4f,0.f };
	memcpy(colorAttachmentClearValue.color.float32, clrClearFloat, sizeof(float) * 4);

	std::vector<VkClearValue> clearValues = 
	{
		colorAttachmentClearValue
	};
	renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassBeginInfo.pClearValues = clearValues.data();

	renderPassBeginInfo.renderArea.extent = swapchain_->getResolution();

	if (framebuffersData_[imgIndex].recorded)
	{
		auto waitResult = vkWaitForFences(device_->getDevice(), 1, &fence, VK_TRUE, 50);
		switch (waitResult)
		{
		case VK_SUCCESS:
			break;
		case VK_TIMEOUT:
			return;
		}
		vkResetFences(device_->getDevice(), 1, &fence);
	}

	vkBeginCommandBuffer(cmdBuffer, &cmdBeginInfo);
	vkCmdBeginRenderPass(cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	////////////////////////////////////////////////////////////
	while (chunksLocked_);
	chunksLocked_ = true;
	////////////////////////
	auto chunks = chunks_;
	////////////////////////
	chunksLocked_ = false;

	for (auto chunk : chunks)
	{
		chunk->executeFrom(cmdBuffer);
	}
	////////////////////////////////////////////////////////////
	vkCmdEndRenderPass(cmdBuffer);
	vkEndCommandBuffer(cmdBuffer);
	framebuffersData_[imgIndex].needUpdate = false;
	framebuffersData_[imgIndex].recorded = true;
}

std::shared_ptr<const Semaphore> Render::send(uint32_t imgIndex, std::shared_ptr<const Semaphore> awaitSemaphore)
{
	if (!framebuffersData_[imgIndex].recorded)
		return {};
	//send command buffer to queue
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &framebuffersData_[imgIndex].cmdBuffer;
	
	std::vector<VkSemaphore> signalSemaphores = { framebuffersData_[imgIndex].renderDoneSemaphore->getSemaphore() };
	std::vector<VkSemaphore> waitSemaphores = { awaitSemaphore->getSemaphore() };
	std::vector<VkPipelineStageFlags> waitFlags = { VK_PIPELINE_STAGE_ALL_COMMANDS_BIT };

	submitInfo.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size());
	submitInfo.pSignalSemaphores = signalSemaphores.data();

	submitInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
	submitInfo.pWaitSemaphores = waitSemaphores.data();
	submitInfo.pWaitDstStageMask = waitFlags.data();

	bool needUpdate = framebuffersData_[imgIndex].dirty && !framebuffersData_[imgIndex].needUpdate;

	auto q = device_->getQueue();
	vkQueueSubmit(q->get(), 1, &submitInfo,
		(needUpdate ? framebuffersData_[imgIndex].fence : VK_NULL_HANDLE));

	if (needUpdate)
	{
		framebuffersData_[imgIndex].needUpdate = true;
		framebuffersData_[imgIndex].dirty = false;
	}

	return framebuffersData_[imgIndex].renderDoneSemaphore;
}

std::shared_ptr<const RenderPass> Render::getRenderPass() const
{
	return renderPass_;
}

void Render::createMainCommandPool()
{
	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	vkCreateCommandPool(device_->getDevice(), &info, nullptr, &mainCommandPool_);
}

void Render::destroyMainCommandPool()
{
	vkDestroyCommandPool(device_->getDevice(), mainCommandPool_, nullptr);
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
	uint32_t imgCount = swapchain_->getImageCount();

	//get swapchain images
	auto vkSwapchain = swapchain_->getSwapchain();
	std::vector<VkImage> images(imgCount);
	vkGetSwapchainImagesKHR(device_->getDevice(), vkSwapchain, &imgCount, images.data());

	framebuffersData_.resize(swapchain_->getImageCount());

	std::vector<VkCommandBuffer> cmdBuffers(imgCount);
	VkCommandBufferAllocateInfo allocateInfo = {};
	allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.commandBufferCount = imgCount;
	allocateInfo.commandPool = mainCommandPool_;
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	vkAllocateCommandBuffers(device_->getDevice(), &allocateInfo, cmdBuffers.data());

	uint32_t imgIdx = 0;
	for (auto &framebufferData : framebuffersData_)
	{
		framebufferData.renderDoneSemaphore = Semaphore::create(device_);
		framebufferData.image = images[imgIdx];
		framebufferData.cmdBuffer = cmdBuffers[imgIdx];

		//create fence
		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		//fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		if (vkCreateFence(device_->getDevice(), &fenceCreateInfo, nullptr, &framebufferData.fence) != VK_SUCCESS)
		{
			//TODO: [OOKAMI] Exception, etc
		}

		//create image view
		VkImageViewCreateInfo imageViewCreateInfo = {};
		imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCreateInfo.image = images[imgIdx];
		imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCreateInfo.format = swapchain_->getFormat();
		imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageViewCreateInfo.subresourceRange.layerCount = 1;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		
		if (vkCreateImageView(device_->getDevice(), &imageViewCreateInfo, nullptr, &framebufferData.imageView) != VK_SUCCESS)
		{
			//TODO: [OOKAMI] Exception, etc
		}

		//create framebuffer
		VkFramebufferCreateInfo framebufferCreateInfo = {};
		framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCreateInfo.renderPass = renderPass_->getRenderPass();
		framebufferCreateInfo.attachmentCount = 1;
		framebufferCreateInfo.pAttachments = &framebufferData.imageView;
		framebufferCreateInfo.layers = 1;
		framebufferCreateInfo.width = swapchain_->getResolution().width;
		framebufferCreateInfo.height = swapchain_->getResolution().height;

		if (vkCreateFramebuffer(device_->getDevice(), &framebufferCreateInfo, nullptr, &framebufferData.framebuffer) != VK_SUCCESS)
		{
			//TODO: [OOKAMI] Exception, etc
		}

		//index increment
		imgIdx++;
	}
}

void Render::destroyFramebuffers()
{
	for (auto &framebufferData : framebuffersData_)
	{
		//destroy framebuffer
		vkDestroyFramebuffer(device_->getDevice(), framebufferData.framebuffer, nullptr);

		//destroy image view
		vkDestroyImageView(device_->getDevice(), framebufferData.imageView, nullptr);

		//destroy fence
		vkDestroyFence(device_->getDevice(), framebufferData.fence, nullptr);
	}
	vkResetCommandPool(device_->getDevice(), mainCommandPool_, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}

void Render::chunkCompiled(std::shared_ptr<const CubA4::render::engine::world::RenderChunk> renderChunk)
{
	while (chunksLocked_);
	chunksLocked_ = true;
	////////////////////////
	chunks_.push_back(renderChunk);
	////////////////////////
	chunksLocked_ = false;
	for (auto &framebuffer : framebuffersData_)
	{
		framebuffer.dirty = true;
	}
}