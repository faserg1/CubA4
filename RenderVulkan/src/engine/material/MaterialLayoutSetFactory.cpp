#include "./MaterialLayoutSetFactory.hpp"
#include "./MaterialLayoutBuilder.hpp"
#include "./MaterialLayout.hpp"
#include "../../vulkan/Pipeline.hpp"
#include "../../vulkan/Device.hpp"
#include <algorithm>
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutSetFactory::MaterialLayoutSetFactory(std::shared_ptr<const Device> device) :
	device_(device)
{
	
}

MaterialLayoutSetFactory::~MaterialLayoutSetFactory()
{
	
}

std::shared_ptr<IMaterialLayoutBuilder> MaterialLayoutSetFactory::createMaterialLayout()
{
	auto builder = std::make_shared<MaterialLayoutBuilder>(device_);
	builders_.push_back(builder);
	return builder;
}

std::vector<std::shared_ptr<const IMaterialLayout>> MaterialLayoutSetFactory::build()
{
	std::vector<std::shared_ptr<const IMaterialLayout>> layouts;
	std::vector<VkGraphicsPipelineCreateInfo> pipelineCreateInfos(builders_.size());
	std::vector<VkPipeline> pipelines(builders_.size());
	VkPipeline *pipelinePtr;
	VkGraphicsPipelineCreateInfo *pipelineCreateInfoPtr = pipelineCreateInfos.data();
	std::for_each(builders_.begin(), builders_.end(), [&pipelineCreateInfoPtr](std::shared_ptr<IMaterialLayoutBuilder> iBuilder)
	{
		auto builder = std::dynamic_pointer_cast<MaterialLayoutBuilder>(iBuilder);
		builder->prepare(*pipelineCreateInfoPtr);

		pipelineCreateInfoPtr++;
	});
	if (vkCreateGraphicsPipelines(device_->getDevice(), VK_NULL_HANDLE,
		static_cast<uint32_t>(pipelineCreateInfos.size()), pipelineCreateInfos.data(), nullptr, pipelines.data()) != VK_SUCCESS)
	{
		//Exceptions, etc
		return {};
	}
	pipelinePtr = pipelines.data();
	pipelineCreateInfoPtr = pipelineCreateInfos.data();
	auto device = device_;
	std::for_each(builders_.begin(), builders_.end(), [&pipelinePtr, &pipelineCreateInfoPtr, &layouts, device](std::shared_ptr<IMaterialLayoutBuilder> iBuilder)
	{
		auto builder = std::dynamic_pointer_cast<MaterialLayoutBuilder>(iBuilder);
		
		PipelineInfo info;
		builder->fillPipelineInfo(info);
		info.pipeline = *pipelinePtr;

		auto pipeline = std::make_shared<Pipeline>(device, info);

		auto materialLayout = std::make_shared<MaterialLayout>(pipeline);

		pipelinePtr++;
		pipelineCreateInfoPtr++;
	});
	return layouts;
}