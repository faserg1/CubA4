#include "./MaterialLayoutSetFactory.hpp"
#include "./MaterialLayoutBuilder.hpp"
#include "./MaterialLayout.hpp"
#include "../ResourceManager.hpp"
#include "../../vulkan/Pipeline.hpp"
#include "../../vulkan/Device.hpp"
#include <cache/ICache.hpp>
#include <cache/ICacheResource.hpp>
#include <algorithm>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutSetFactory::MaterialLayoutSetFactory(std::shared_ptr<const Device> device,
	std::shared_ptr<const Render> render, std::shared_ptr<const ResourceManager> resourceManager) :
	device_(device), render_(render), resourceManager_(resourceManager)
{
	
}

MaterialLayoutSetFactory::~MaterialLayoutSetFactory()
{
	
}

std::shared_ptr<IMaterialLayoutBuilder> MaterialLayoutSetFactory::createMaterialLayout()
{
	auto builder = std::make_shared<MaterialLayoutBuilder>(device_, render_, resourceManager_);
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
	
	const std::string cacheFilename = "pipelineCache.data";
	auto cache = resourceManager_->getCache();
	std::shared_ptr<void> cacheData;

	VkPipelineCache pipelineCache = {};
	VkPipelineCacheCreateInfo cacheInfo = {};
	cacheInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

	if (cache->exists(cacheFilename))
	{
		auto cacheFile = cache->get(cacheFilename);
		cacheData = std::static_pointer_cast<unsigned char>(cacheFile->load());
		cacheInfo.pInitialData = cacheData.get();
		cacheInfo.initialDataSize = cacheFile->size();
	}

	if (vkCreatePipelineCache(device_->getDevice(), &cacheInfo, nullptr, &pipelineCache) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] LOG. Do not return. We can live without cache
	}
	if (vkCreateGraphicsPipelines(device_->getDevice(), pipelineCache,
		static_cast<uint32_t>(pipelineCreateInfos.size()), pipelineCreateInfos.data(), nullptr, pipelines.data()) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return {};
	}
	//Save cache if available
	if (pipelineCache)
	{
		size_t saveSize = {};
		if (vkGetPipelineCacheData(device_->getDevice(), pipelineCache, &saveSize, nullptr) == VK_SUCCESS)
		{
			auto *data = new unsigned char[saveSize];
			if (vkGetPipelineCacheData(device_->getDevice(), pipelineCache, &saveSize, data) == VK_SUCCESS)
			{
				auto cacheFile = cache->get(cacheFilename);
				cacheFile->save(data, saveSize);
			}
			else
			{
				// TODO: [OOKAMI] LOG. Do not return. We can live without saving cache
			}
			delete [] data;
		}
		else
		{
			// TODO: [OOKAMI] LOG. Do not return. We can live without saving cache
		}

		vkDestroyPipelineCache(device_->getDevice(), pipelineCache, nullptr);
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

		auto materialLayout = std::make_shared<MaterialLayout>(pipeline, builder->getTextureLayout());
		layouts.push_back(materialLayout);

		pipelinePtr++;
		pipelineCreateInfoPtr++;
	});
	return layouts;
}