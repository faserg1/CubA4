#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <string>
#include <vulkan/Device.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>

namespace CubA4::render::engine
{
	class ResourceManager;
}

namespace CubA4::render::vulkan
{
    class Device;

    class PipelineCache
    {
    public:
        PipelineCache(std::shared_ptr<const Device> device, std::shared_ptr<const CubA4::render::engine::ResourceManager> resourceManager);
        ~PipelineCache();

        VkPipelineCache getCache() const;
    private:
        const std::shared_ptr<const Device> device_;
        const std::shared_ptr<const CubA4::render::engine::ResourceManager> resourceManager_;
        const std::string cacheFilename_ = "pipelineCache.data";
        VkPipelineCache cache_;
    };
}