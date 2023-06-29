#include <engine/RenderPassManager.hpp>
using namespace CubA4::render::engine;

RenderPassManager::RenderPassManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), config_(config)
{

}

void RenderPassManager::createRenderPasses(VkFormat imageFormat)
{
	using namespace CubA4::render::vulkan;
	// main render pass
	{
		RenderPassBuilder builder(device_, config_);
		// 
		// steal from builder some things
		auto colorIndex = builder.addDescription(imageFormat, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, true, LoadOp::Clear, StoreOp::DontCare);
		auto depthIndex = builder.addDescription(VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, true, LoadOp::Clear, StoreOp::Store);
		auto resolveIndex = builder.addDescription(imageFormat, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, false, LoadOp::DontCare, StoreOp::Store);

		// remember if VK_ATTACHMENT_UNUSED 

		auto worldSubpassIndex = builder.addSubpass();

		builder.addColorReference(
			worldSubpassIndex,
			colorIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			depthIndex, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			resolveIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		);

		mainInfo_.worldSubpass = worldSubpassIndex;

		mainRenderPass_ = builder.build();
		device_->getMarker().setName(mainRenderPass_->getRenderPass(), "Default Render Pass");
	}
	
	// debug render pass
	{
		/*
		Moving to the next subpass automatically performs any multisample resolve operations in the subpass being ended.
		End-of-subpass multisample resolves are treated as color attachment writes for the purposes of synchronization.
		This applies to resolve operations for both color and depth/stencil attachments.
		That is, they are considered to execute in the VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT pipeline stage
		and their writes are synchronized with VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT.
		Synchronization between rendering within a subpass and any resolve operations at the end of the subpass occurs automatically,
		without need for explicit dependencies or pipeline barriers.
		However, if the resolve attachment is also used in a different subpass, an explicit dependency is needed.
		*/

		RenderPassBuilder builderDebug(device_, config_);

		auto colorIndexDebug = builderDebug.addDescription(imageFormat, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, false, LoadOp::Load, StoreOp::Store, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
		auto depthIndexDebug = builderDebug.addDescription(VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, true, LoadOp::Load, StoreOp::DontCare, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
		auto depthResolveIndexDebug = builderDebug.addDescription(VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, false, LoadOp::Load, StoreOp::Store, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

		auto resolveDepthSubpass = builderDebug.addSubpass();
	
		// resolve

		builderDebug.addColorReference(
			resolveDepthSubpass,
			VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_UNDEFINED,
			depthIndexDebug, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_UNDEFINED
		);

		VkAttachmentReference2 resolveDepthAttachment {
			.sType = VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2,
			.attachment = depthResolveIndexDebug,
			.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		};

		VkSubpassDescriptionDepthStencilResolve dsNext {
			.sType = VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE,
			.depthResolveMode = VK_RESOLVE_MODE_AVERAGE_BIT,
			.pDepthStencilResolveAttachment = builderDebug.addExternalColorReference(resolveDepthSubpass, resolveDepthAttachment)
		};

		builderDebug.addSubpassDescNext(resolveDepthSubpass, dsNext);

		// color

		auto debugSubpassIndex = builderDebug.addSubpass();

		builderDebug.addColorReference(
			debugSubpassIndex,
			colorIndexDebug, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			depthResolveIndexDebug, VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
			VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_UNDEFINED
		);

		/// deps

		VkSubpassDependency2 depthPrev {
			.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2,
			.srcSubpass = VK_SUBPASS_EXTERNAL,
			.dstSubpass = resolveDepthSubpass,
			.srcStageMask = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT ,
    		.dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
    		.srcAccessMask = 0,
    		.dstAccessMask = 0,
			.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
		};

		builderDebug.addDependency(depthPrev);

		VkSubpassDependency2 resolveDepth {
			.sType = VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2,
			.srcSubpass = resolveDepthSubpass,
			.dstSubpass = debugSubpassIndex,
			.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
    		.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
    		.srcAccessMask = 0,
    		.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
			.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
		};

		builderDebug.addDependency(resolveDepth);

		debugInfo_.debugSubpass = debugSubpassIndex;

		debugRenderPass_ = builderDebug.build();
		device_->getMarker().setName(debugRenderPass_->getRenderPass(), "Debug Render Pass");
	}
}

std::shared_ptr<CubA4::render::vulkan::RenderPass> RenderPassManager::getMainRenderPass() const
{
	return mainRenderPass_;
}

std::shared_ptr<CubA4::render::vulkan::RenderPass> RenderPassManager::getDebugRenderPass() const
{
	return debugRenderPass_;
}

const MainRenderPassInfo& RenderPassManager::getMainInfo() const
{
	return mainInfo_;
}

const DebugRenderPassInfo& RenderPassManager::getDebugInfo() const
{
	return debugInfo_;
}