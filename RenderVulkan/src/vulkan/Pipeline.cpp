#include "./Pipeline.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

Pipeline::Pipeline(std::shared_ptr<const Device> device, VkPipeline pipeline, VkPipelineLayout layout, VkPipelineBindPoint bindPoint) :
	device_(device), pipeline_(pipeline), layout_(layout), bindPoint_(bindPoint)
{

}

Pipeline::~Pipeline()
{
	vkDestroyPipeline(device_->getDevice(), pipeline_, nullptr);
	vkDestroyPipelineLayout(device_->getDevice(), layout_, nullptr);
}

void Pipeline::bind(VkCommandBuffer cmdBuf) const
{
	vkCmdBindPipeline(cmdBuf, bindPoint_, pipeline_);
}

VkPipeline Pipeline::getPipeline() const
{
	return pipeline_;
}

VkPipelineLayout Pipeline::getLayout() const
{
	return layout_;
}

VkPipelineBindPoint Pipeline::getBindPoint() const
{
	return bindPoint_;
}