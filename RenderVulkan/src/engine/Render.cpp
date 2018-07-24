#include "./Render.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Swapchain.hpp"
#include "../vulkan/Semaphore.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

Render::Render(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain) :
	device_(device), swapchain_(swapchain)
{
	createMainCommandPool();
	createRenderPass();
	createFramebuffers();
}

Render::~Render()
{
	vkQueueWaitIdle(device_->getQueue());
	destroyFramebuffers();
	destroyRenderPass();
	destroyMainCommandPool();
}

void Render::record(uint32_t imgIndex)
{
	auto cmdBuffer = framebuffersData_[imgIndex].cmdBuffer;
	auto framebuffer = framebuffersData_[imgIndex].framebuffer;

	VkCommandBufferBeginInfo cmdBeginInfo = {};
	cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(cmdBuffer, &cmdBeginInfo);

	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.framebuffer = framebuffer;
	renderPassBeginInfo.renderPass = renderPass_;

	VkClearValue colorAttachmentClearValue = {};
	int32_t *colorAttachmentClearValueInt32 = colorAttachmentClearValue.color.int32;
	colorAttachmentClearValueInt32[0] = 255;

	std::vector<VkClearValue> clearValues = 
	{
		colorAttachmentClearValue
	};
	renderPassBeginInfo.clearValueCount = clearValues.size();
	renderPassBeginInfo.pClearValues = clearValues.data();

	renderPassBeginInfo.renderArea.extent = swapchain_->getResolution();

	vkCmdBeginRenderPass(cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	//record in parallel second command buffers (subpasses)

	vkCmdEndRenderPass(cmdBuffer);
	vkEndCommandBuffer(cmdBuffer);
}

std::shared_ptr<const Semaphore> Render::send(uint32_t imgIndex, std::shared_ptr<const Semaphore> awaitSemaphore)
{
	//send command buffer to queue
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &framebuffersData_[imgIndex].cmdBuffer;
	
	std::vector<VkSemaphore> signalSemaphores = { framebuffersData_[imgIndex].renderDoneSemaphore->getSemaphore() };
	std::vector<VkSemaphore> waitSemaphores = { awaitSemaphore->getSemaphore() };
	std::vector<VkPipelineStageFlags> waitFlags = { VK_PIPELINE_STAGE_ALL_COMMANDS_BIT };

	submitInfo.signalSemaphoreCount = signalSemaphores.size();
	submitInfo.pSignalSemaphores = signalSemaphores.data();

	submitInfo.waitSemaphoreCount = waitSemaphores.size();
	submitInfo.pWaitSemaphores = waitSemaphores.data();
	submitInfo.pWaitDstStageMask = waitFlags.data();

	vkQueueSubmit(device_->getQueue(), 1, &submitInfo, VK_NULL_HANDLE);

	return framebuffersData_[imgIndex].renderDoneSemaphore;
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
	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	//Рассчитывать будем на то, что у нас сейчас только один выход - цвет, и ничего нет на вход.
	//После здесь добавятся буфер глубины и т.д. и т.п
	//Не забыть про всю эту фигню при создании фреймбуфера и очистке (в начале прохода рендеринга)
	
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = swapchain_->getFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	std::vector<VkAttachmentDescription> attachments =
	{
		colorAttachment
	};

	renderPassCreateInfo.attachmentCount = attachments.size();
	renderPassCreateInfo.pAttachments = attachments.data();

	VkAttachmentReference colorAttachmentReference = {};
	colorAttachmentReference.attachment = 0;
	colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//И так, по началу будем расчитывать на то, что существует один проход рендеринга с одним подпроходом.
	//В дальнейшем подпроходов может быть больше, к примеру:
	//Отрисовка атмосферы (кубмап), отрисовка основных объектов, отрисовка скелетонов, где то тут прозрачные объекты, пост обработка
	
	VkSubpassDescription mainSubpass = {};
	mainSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	mainSubpass.colorAttachmentCount = 1;
	mainSubpass.pColorAttachments = &colorAttachmentReference;

	std::vector<VkSubpassDescription> subpasses =
	{
		mainSubpass
	};

	renderPassCreateInfo.subpassCount = subpasses.size();
	renderPassCreateInfo.pSubpasses = subpasses.data();

	if (vkCreateRenderPass(device_->getDevice(), &renderPassCreateInfo, nullptr, &renderPass_) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
	}
}

void Render::destroyRenderPass()
{
	vkDestroyRenderPass(device_->getDevice(), renderPass_, nullptr);
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
		framebufferCreateInfo.renderPass = renderPass_;
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
	}
	vkResetCommandPool(device_->getDevice(), mainCommandPool_, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}