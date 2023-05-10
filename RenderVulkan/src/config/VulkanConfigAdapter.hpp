#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <config/IRenderConfig.hpp>


namespace CubA4::render::config
{
	class VulkanConfigAdapter
    {
    public:
        VulkanConfigAdapter(std::shared_ptr<const config::IRenderConfig> config);

        std::shared_ptr<const config::IRenderConfig> getConfig() const;

        VkSampleCountFlagBits getAntialiasing() const;
    private:
        const std::shared_ptr<const config::IRenderConfig> config_;
    };
}