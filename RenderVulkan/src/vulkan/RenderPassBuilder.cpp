#include "./RenderPassBuilder.hpp"
#include "./RenderPass.hpp"
#include "./Device.hpp"
#include "./Swapchain.hpp"
using namespace CubA4::render::vulkan;

RenderPassBuilder::RenderPassBuilder(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), config_(config)
{

}

RenderPassBuilder::~RenderPassBuilder()
{
	
}

std::shared_ptr<RenderPass> RenderPassBuilder::build()
{
	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments_.size());
	renderPassCreateInfo.pAttachments = attachments_.data();

	//////////////////////////////////////////////

	renderPassCreateInfo.subpassCount = static_cast<uint32_t>(subpassesDesc_.size());
	renderPassCreateInfo.pSubpasses = subpassesDesc_.data();

	//////////////////////////////////////////////

	// TODO: [OOKAMI] Move deps out

	std::vector<VkSubpassDependency> deps
	{
	};
	

	renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(deps.size());
	renderPassCreateInfo.pDependencies = deps.data();

	//////////////////////////////////////////////

	VkRenderPass renderPass;
	if (vkCreateRenderPass(device_->getDevice(), &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
	}
	device_->getMarker().setName(renderPass, "Default Render Pass");
	return std::make_shared<RenderPass>(device_, renderPass);
}

uint32_t RenderPassBuilder::addDescription(VkFormat format, VkImageLayout finalLayout, bool antialiasing, LoadOp loadOp, StoreOp storeOp)
{
	VkAttachmentDescription description {};
	description.format = format;
	description.samples = antialiasing ? config_.getAntialiasing() : VK_SAMPLE_COUNT_1_BIT;
	switch (loadOp)
	{
	case LoadOp::Load:
		description.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
		break;
	case LoadOp::Clear:
		description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		break;
	case LoadOp::DontCare:
		description.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		break;
	}
	switch (storeOp)
	{
	case StoreOp::DontCare:
		description.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		break;
	case StoreOp::Store:
		description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		break;
	}
	description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	description.finalLayout = finalLayout;
	attachments_.push_back(description);
	return static_cast<uint32_t>(attachments_.size() - 1);
}

void RenderPassBuilder::addColorReference(uint32_t subpassIndex, uint32_t idxColor, VkImageLayout layoutColor, uint32_t idxDepth, VkImageLayout layoutDepth, uint32_t idxResolve, VkImageLayout layoutResolve)
{
	// assert subpass index

	auto &subpassInfo = subpasses_[subpassIndex];

	VkAttachmentReference color
	{
		.attachment = idxColor,
		.layout = layoutColor
	};

	VkAttachmentReference depth
	{
		.attachment = idxDepth,
		.layout = layoutDepth
	};

	VkAttachmentReference resolve
	{
		.attachment = idxResolve,
		.layout = layoutResolve
	};

	subpassInfo.referencesColor_.color.push_back(color);
	subpassInfo.referencesColor_.depth.push_back(depth);
	subpassInfo.referencesColor_.resolve.push_back(resolve);

	auto &subpass = subpassesDesc_[subpassIndex];
	subpass.colorAttachmentCount = static_cast<uint32_t>(subpassInfo.referencesColor_.color.size());
	subpass.pColorAttachments = subpassInfo.referencesColor_.color.data();
	subpass.pDepthStencilAttachment = subpassInfo.referencesColor_.depth.data();
	subpass.pResolveAttachments = subpassInfo.referencesColor_.resolve.data();
}

uint32_t RenderPassBuilder::addSubpass()
{
	subpasses_.push_back({});
	subpassesDesc_.push_back({});

	// assert(subpasses_.size() == subpassesDesc_.size());

	auto idx = static_cast<uint32_t>(subpasses_.size() - 1);

	auto &subpass = subpassesDesc_[idx];
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	return idx;
}