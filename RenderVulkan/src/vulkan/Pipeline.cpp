#include "./Pipeline.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

Pipeline::Pipeline(std::shared_ptr<const Device> device, PipelineInfo info) :
	device_(device), pipeline_(info.pipeline), layout_(info.layout), bindPoint_(info.bindPoint),
	descriptorSetLayouts_(info.descriptorSetLayouts), shaders_(info.shaders)
{

}

Pipeline::~Pipeline()
{
	vkDestroyPipeline(device_->getDevice(), pipeline_, nullptr);
	vkDestroyPipelineLayout(device_->getDevice(), layout_, nullptr);

	for (auto descriptorSetLayout : descriptorSetLayouts_)
	{
		vkDestroyDescriptorSetLayout(device_->getDevice(), descriptorSetLayout, nullptr);
	}
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