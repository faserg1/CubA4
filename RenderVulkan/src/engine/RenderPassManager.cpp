#include <engine/RenderPassManager.hpp>
using namespace CubA4::render::engine;

RenderPassManager::RenderPassManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), config_(config)
{

}

void RenderPassManager::createRenderPasses(VkFormat imageFormat)
{
	using namespace CubA4::render::vulkan;

	RenderPassBuilder builder(device_, config_);
	// steal from builder some things
	auto colorIndex = builder.addDescription(imageFormat, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, true, LoadOp::Clear, StoreOp::DontCare);
	auto depthIndex = builder.addDescription(VK_FORMAT_D32_SFLOAT_S8_UINT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, true, LoadOp::Clear, StoreOp::Store);
	auto resolveIndex = builder.addDescription(imageFormat, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, false, LoadOp::DontCare, StoreOp::Store);

	// remember if VK_ATTACHMENT_UNUSED 

	auto subpassIndex = builder.addSubpass();

	builder.addColorReference(
		subpassIndex,
		colorIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		depthIndex, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		resolveIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	);

	mainRenderPass_ = builder.build();
}

std::shared_ptr<CubA4::render::vulkan::RenderPass> RenderPassManager::getMainRenderPass() const
{
	return mainRenderPass_;
}