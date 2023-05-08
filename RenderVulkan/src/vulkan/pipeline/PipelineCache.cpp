#include <vulkan/pipeline/PipelineCache.hpp>
#include <engine/ResourceManager.hpp>
using namespace CubA4::render::vulkan;

PipelineCache::PipelineCache(std::shared_ptr<const Device> device, std::shared_ptr<const CubA4::render::engine::ResourceManager> resourceManager) :
    device_(device), resourceManager_(resourceManager)
{
    VkPipelineCacheCreateInfo cacheInfo = {};
	cacheInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;

	if (auto cache = resourceManager_->getCache(cacheFilename_); cache && cache->exists())
	{
		auto data = cache->data();
		cacheInfo.pInitialData = data.first.get();
		cacheInfo.initialDataSize = data.second;
	}

	if (vkCreatePipelineCache(device_->getDevice(), &cacheInfo, nullptr, &cache_) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] LOG. We can live without cache
	}
}

PipelineCache::~PipelineCache()
{
    if (!cache_)
        return;
    size_t saveSize = {};
    if (vkGetPipelineCacheData(device_->getDevice(), cache_, &saveSize, nullptr) == VK_SUCCESS)
    {
        auto *data = new unsigned char[saveSize];
        if (vkGetPipelineCacheData(device_->getDevice(), cache_, &saveSize, data) == VK_SUCCESS)
        {
            if (auto cache = resourceManager_->getCache(cacheFilename_))
                cache->save(data, saveSize);
        }
        else
        {
            // TODO: [OOKAMI] LOG. We can live without saving cache
        }
        delete [] data;
    }
    else
    {
        // TODO: [OOKAMI] LOG. We can live without saving cache
    }

    vkDestroyPipelineCache(device_->getDevice(), cache_, nullptr);	
}

VkPipelineCache PipelineCache::getCache() const
{
    return cache_;
}