#include <engine/framebuffer/DebugFramebufferManager.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;


DebugFramebufferManager::DebugFramebufferManager(
	std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	FramebufferManager(device, config)
{

}

void DebugFramebufferManager::setMainDepths(std::vector<VkImage> mainDepths)
{
	mainDepths_ = std::move(mainDepths);
}

void DebugFramebufferManager::onSwapchainUpdateInternal(std::shared_ptr<const vulkan::Swapchain> swapchain)
{
	CubA4::render::vulkan::FramebuffersBuilder builder(device_, commandPool_, config_);

	builder.addAttachmentInfo({
		.type = AttachmentInfo::Type::Present,
		.aspect = VK_IMAGE_ASPECT_COLOR_BIT
	});

	builder.addAttachmentInfo({
		.type = AttachmentInfo::Type::Depth,
		.external = mainDepths_,
		.aspect = VK_IMAGE_ASPECT_DEPTH_BIT,
	});

	builder.addAttachmentInfo({
		.type = AttachmentInfo::Type::Depth,
		.additionalUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		.aspect = VK_IMAGE_ASPECT_DEPTH_BIT,
		.enableAA = false
	});

	framebuffers_ = builder.createFramebuffers(swapchain, renderPass_.lock());
	for (auto framebuffer : framebuffers_)
	{
		auto cmdBuffer = framebuffer->getCommandBuffer();
		device_->getMarker().setName(cmdBuffer, "Debug cmd buffer");
	}

	attachmentsCount_ = builder.getAttachmentsCount();
}