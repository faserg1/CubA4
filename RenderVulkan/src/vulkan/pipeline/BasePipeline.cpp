#include "./BasePipeline.hpp"
#include "../Device.hpp"
#include <stdexcept>
using namespace CubA4::render::vulkan::pipeline;
using namespace CubA4::render::vulkan;

BasePipeline::BasePipeline(std::shared_ptr<VulkanDevice> device)
{
	
}

BasePipeline::~BasePipeline()
{
	
}

VkPipeline BasePipeline::getPipeline() const
{
	return pipeline_;
}

VkPipelineLayout BasePipeline::getPipelineLayout() const
{
	return pipelineLayout_;
}

void BasePipeline::init()
{
	auto layoutInfo = getPipelineLayoutCreateInfo();
	if (vkCreatePipelineLayout(device_->getDevice(), &layoutInfo, nullptr, &pipelineLayout_) != VK_SUCCESS)
		throw std::runtime_error("Unable to create pipeline layout.");
	auto pipelineInfo = getPipelineCreateInfo();
	if (vkCreateGraphicsPipelines(device_->getDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline_) != VK_SUCCESS)
		throw std::runtime_error("Unable to create pipeline.");
}

void BasePipeline::destroy()
{
	vkDestroyPipeline(device_->getDevice(), pipeline_, nullptr);
	vkDestroyPipelineLayout(device_->getDevice(), pipelineLayout_, nullptr);
}