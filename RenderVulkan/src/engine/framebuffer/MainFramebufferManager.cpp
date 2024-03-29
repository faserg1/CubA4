#include <engine/framebuffer/MainFramebufferManager.hpp>
#include <fmt/format.h>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;


MainFramebufferManager::MainFramebufferManager(
	std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	FramebufferManager(device, config)
{

}

void MainFramebufferManager::onSwapchainUpdateInternal(std::shared_ptr<const vulkan::Swapchain> swapchain)
{
	CubA4::render::vulkan::FramebuffersBuilder builder(device_, commandPool_, config_);

	builder.addAttachmentInfo({
		.type = AttachmentInfo::Type::Color,
		.additionalUsage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
		.aspect = VK_IMAGE_ASPECT_COLOR_BIT,
		.enableAA = true
	});

	builder.addAttachmentInfo({
		.type = AttachmentInfo::Type::Depth,
		.additionalUsage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
		.aspect = VK_IMAGE_ASPECT_DEPTH_BIT,
		.enableAA = true
	});

	builder.addAttachmentInfo({
		.type = AttachmentInfo::Type::Present,
		.aspect = VK_IMAGE_ASPECT_COLOR_BIT
	});

	framebuffers_ = builder.createFramebuffers(swapchain, renderPass_.lock());
	size_t fmNum = 0;
	for (auto framebuffer : framebuffers_)
	{
		auto cmdBuffer = framebuffer->getCommandBuffer();
		auto debugName = fmt::format("Main cmd buffer #{}", fmNum++);
		device_->getMarker().setName(cmdBuffer, debugName);
	}

	attachmentsCount_ = builder.getAttachmentsCount();
}