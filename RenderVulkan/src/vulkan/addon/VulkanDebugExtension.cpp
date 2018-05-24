#include "./VulkanDebugExtension.hpp"
#include <vulkan/vulkan.h>
#include "../VulkanInstance.hpp"
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::core::logging;

#define getVkFuncInstancePtr(instance, funcName) (PFN_##funcName)(vkGetInstanceProcAddr(instance, #funcName))

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanDebugExtensionData
				{
					VkDebugUtilsMessengerEXT messeger;

					PFN_vkCreateDebugUtilsMessengerEXT createDebugUtils;
					PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtils;
				};
			}
		}
	}
}

VulkanDebugExtension::VulkanDebugExtension(std::shared_ptr<ILogger> logger) :
	data_(std::make_shared<VulkanDebugExtensionData>())
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

void VulkanDebugExtension::init(std::shared_ptr<const VulkanInstance> instance)
{
	fillFunctionPointers(instance);
	VkDebugUtilsMessengerCreateInfoEXT callback;
	callback.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	callback.pNext = nullptr;
	callback.flags = 0;
	callback.messageType =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
	auto logCallback = [](
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
		void *pUserData) -> VkBool32
	{
		auto *loggerTagged = (ILoggerTagged*) pUserData;
		LogLevel level;
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			level = LogLevel::Error;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			level = LogLevel::Warning;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			level = LogLevel::Info;
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			level = LogLevel::Debug;
			break;
			loggerTagged->log(level, pCallbackData->pMessage);
		}
		return VK_FALSE;
	};
	callback.pfnUserCallback = logCallback;
	callback.pUserData = (void *) &(*loggerTagged_);
	data_->createDebugUtils(instance->get(), &callback, nullptr, &data_->messeger);
}

void VulkanDebugExtension::destroy(std::shared_ptr<const VulkanInstance> instance)
{
	data_->destroyDebugUtils(instance->get(), data_->messeger, nullptr);
	data_->messeger = {};
}

void VulkanDebugExtension::fillFunctionPointers(std::shared_ptr<const VulkanInstance> instance)
{
	auto vkInstance = instance->get();
	data_->createDebugUtils = getVkFuncInstancePtr(vkInstance, vkCreateDebugUtilsMessengerEXT);
	data_->destroyDebugUtils = getVkFuncInstancePtr(vkInstance, vkDestroyDebugUtilsMessengerEXT);
}
