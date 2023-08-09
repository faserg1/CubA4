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
	VkRenderPassCreateInfo2 renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2;

	renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments_.size());
	renderPassCreateInfo.pAttachments = attachments_.data();

	//////////////////////////////////////////////

	renderPassCreateInfo.subpassCount = static_cast<uint32_t>(subpassesDesc_.size());
	renderPassCreateInfo.pSubpasses = subpassesDesc_.data();

	//////////////////////////////////////////////

	renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(deps_.size());
	renderPassCreateInfo.pDependencies = deps_.data();

	//////////////////////////////////////////////

	VkRenderPass renderPass;
	if (vkCreateRenderPass2(device_->getDevice(), &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
	}
	return std::make_shared<RenderPass>(device_, renderPass);
}

uint32_t RenderPassBuilder::addDescription(VkFormat format, VkImageLayout finalLayout, bool antialiasing, LoadOp loadOp, StoreOp storeOp, VkImageLayout initLayout)
{
	VkAttachmentDescription2 description {};
	description.sType = VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2;
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
	description.initialLayout = initLayout;
	description.finalLayout = finalLayout;
	attachments_.push_back(description);
	return static_cast<uint32_t>(attachments_.size() - 1);
}

void RenderPassBuilder::addColorReference(uint32_t subpassIndex, uint32_t idxColor, VkImageLayout layoutColor, uint32_t idxDepth, VkImageLayout layoutDepth, uint32_t idxResolve, VkImageLayout layoutResolve)
{
	// assert subpass index

	auto &subpassInfo = subpasses_[subpassIndex];

	VkAttachmentReference2 color
	{
		.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2,
		.attachment = idxColor,
		.layout = layoutColor
	};

	VkAttachmentReference2 depth
	{
		.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2,
		.attachment = idxDepth,
		.layout = layoutDepth
	};

	VkAttachmentReference2 resolve
	{
		.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2,
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

VkAttachmentReference2 *RenderPassBuilder::addExternalColorReference(uint32_t subpassTo, const VkAttachmentReference2 &reference)
{
	auto ptr = std::make_unique<VkAttachmentReference2>(reference);
	auto savePtr = ptr.get();
	subpasses_[subpassTo].referencesColor_.external.push_back(std::move(ptr));
	return savePtr;
}

uint32_t RenderPassBuilder::addSubpass()
{
	subpasses_.push_back({});
	subpassesDesc_.push_back(VkSubpassDescription2 {
		.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2,
	});

	// assert(subpasses_.size() == subpassesDesc_.size());

	auto idx = static_cast<uint32_t>(subpasses_.size() - 1);

	auto &subpass = subpassesDesc_[idx];
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	return idx;
}

uint32_t RenderPassBuilder::subpassCount() const
{
	return static_cast<uint32_t>(subpasses_.size());
}

void RenderPassBuilder::addDependency(VkSubpassDependency2 dependency)
{
	deps_.push_back(dependency);
}