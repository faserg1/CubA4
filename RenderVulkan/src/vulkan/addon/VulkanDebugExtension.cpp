#include "./VulkanDebugExtension.hpp"
#include <vulkan/vulkan.h>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::core::logging;

VulkanDebugExtension::VulkanDebugExtension(std::shared_ptr<ILogger> logger)
{
	loggerTagged_ = std::shared_ptr<ILoggerTagged>(logger->createTaggedLog(LogSourceSystem::Render, "VULKAN"));
}

VulkanDebugExtension::~VulkanDebugExtension()
{
	
}

std::vector<std::string> VulkanDebugExtension::names() const
{
	return { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
}

void VulkanDebugExtension::init(std::shared_ptr<VulkanInstance> instance)
{

}

void VulkanDebugExtension::destroy(std::shared_ptr<VulkanInstance> instance)
{

}