#include <config/VulkanConfigAdapter.hpp>
#include <vulkan/util/ConfigConverter.hpp>>
using namespace CubA4::render::config;

VulkanConfigAdapter::VulkanConfigAdapter(std::shared_ptr<const config::IRenderConfig> config) :
    config_(config)
{

}

std::shared_ptr<const CubA4::render::config::IRenderConfig> VulkanConfigAdapter::getConfig() const
{
    return config_;
}

VkSampleCountFlagBits VulkanConfigAdapter::getAntialiasing() const
{
    return CubA4::render::vulkan::util::convertAntialiasing(config_->getAntialiasing());
}