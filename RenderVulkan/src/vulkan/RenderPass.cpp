#include "./RenderPass.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

RenderPass::RenderPass(std::shared_ptr<const Device> device, VkRenderPass renderPass) :
	device_(device), renderPass_(renderPass)
{

	
}

RenderPass::~RenderPass()
{
	vkDestroyRenderPass(device_->getDevice(), renderPass_, nullptr);
}

VkRenderPass RenderPass::getRenderPass() const
{
	return renderPass_;
}