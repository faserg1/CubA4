#include "./MaterialLayoutSetFactory.hpp"
#include "./MaterialLayoutBuilder.hpp"
#include "./MaterialLayout.hpp"
#include "../ResourceManager.hpp"
#include <vulkan/pipeline/PipelineBuilderMaterial.hpp>
#include <vulkan/pipeline/PipelineCache.hpp>
#include <vulkan/pipeline/Pipeline.hpp>
#include <vulkan/Device.hpp>
#include <algorithm>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutSetFactory::MaterialLayoutSetFactory(std::shared_ptr<const Device> device,
	std::shared_ptr<const RenderPassManager> rpManager, std::shared_ptr<const ResourceManager> resourceManager,
	CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), rpManager_(rpManager), resourceManager_(resourceManager), config_(config)
{
	
}

MaterialLayoutSetFactory::~MaterialLayoutSetFactory()
{
	
}

std::shared_ptr<IMaterialLayoutBuilder> MaterialLayoutSetFactory::createMaterialLayout()
{
	auto builder = std::make_shared<MaterialLayoutBuilder>(device_, rpManager_, resourceManager_, config_);
	builders_.push_back(builder);
	return builder;
}

// TODO: Should not work as singleton

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
	
	const std::string cacheFilename = "pipelineCache.data";

	PipelineCache pipelineCache(device_, resourceManager_);

	if (vkCreateGraphicsPipelines(device_->getDevice(), pipelineCache.getCache(),
		static_cast<uint32_t>(pipelineCreateInfos.size()), pipelineCreateInfos.data(), nullptr, pipelines.data()) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return {};
	}

	pipelinePtr = pipelines.data();
	pipelineCreateInfoPtr = pipelineCreateInfos.data();
	auto device = device_;
	std::for_each(builders_.begin(), builders_.end(), [this, &pipelinePtr, &pipelineCreateInfoPtr, &layouts, device](std::shared_ptr<IMaterialLayoutBuilder> iBuilder)
	{
		auto builder = std::dynamic_pointer_cast<MaterialLayoutBuilder>(iBuilder);
		
		PipelineInfo info;
		builder->fillPipelineInfo(info);
		info.pipeline = *pipelinePtr;

		auto pipeline = std::make_shared<Pipeline>(device, info);

		auto materialLayout = std::make_shared<MaterialLayout>(pipeline, builder->getTextureLayout());
		layouts.push_back(materialLayout);

		pipelinePtr++;
		pipelineCreateInfoPtr++;
	});
	builders_.clear();
	return layouts;
}
