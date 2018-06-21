#include "./StandardPipeline.hpp"
using namespace CubA4::render::vulkan::pipeline;
using namespace CubA4::render::vulkan;

StandardPipeline::StandardPipeline(std::shared_ptr<VulkanDevice> device) :
	BasePipeline(device)
{
	
}

StandardPipeline::~StandardPipeline()
{
	
}

std::shared_ptr<StandardPipeline> StandardPipeline::create(std::shared_ptr<VulkanDevice> device)
{
	auto ptr = std::shared_ptr<StandardPipeline>(new StandardPipeline(device), [](StandardPipeline *ptr)
	{
		ptr->destroy();
		delete ptr;
	});
	return ptr;
}

VkPipelineLayoutCreateInfo &StandardPipeline::getPipelineLayoutCreateInfo() const
{

}

VkGraphicsPipelineCreateInfo &StandardPipeline::getPipelineCreateInfo() const
{

}