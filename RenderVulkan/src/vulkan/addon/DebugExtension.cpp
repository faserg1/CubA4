#include "./DebugExtension.hpp"
#include <vulkan/vulkan.h>
#include "../Instance.hpp"
#include <config/IRenderConfig.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::logging;
using namespace CubA4::render::config;

#define getVkFuncInstancePtr(instance, funcName) (PFN_##funcName)(vkGetInstanceProcAddr(instance, #funcName))

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct DebugExtensionData
				{
					VkDebugUtilsMessengerEXT messeger;
					VkDebugReportCallbackEXT callback;

					PFN_vkCreateDebugUtilsMessengerEXT createDebugUtils;
					PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtils;

					PFN_vkCreateDebugReportCallbackEXT createDebugReportCallback;
					PFN_vkDestroyDebugReportCallbackEXT destroyDebugReportCallback;
				};
			}
		}
	}
}

DebugExtension::DebugExtension(std::shared_ptr<ILogger> logger, std::shared_ptr<IRenderConfig> cfg) :
	loggerTagged_(logger->createTaggedLog(LogSourceSystem::Render, "VULKAN")), data_(std::make_shared<DebugExtensionData>())
{
	logLevel_ = cfg->getLoggingLevel();
	if (logLevel_ < 0 || logLevel_ > 4)
		logLevel_ = 3;
	cfg->setLoggingLevel(logLevel_);
}

DebugExtension::~DebugExtension()
{
	
}

std::vector<std::string> DebugExtension::names() const
{
	return { VK_EXT_DEBUG_UTILS_EXTENSION_NAME, VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
}

void DebugExtension::init(std::shared_ptr<const Instance> instance)
{
	if (!instance)
		return;
	fillFunctionPointers(instance);
	createDebugUtils(instance);
	//createDebugReport(instance);
}

void DebugExtension::destroy(std::shared_ptr<const Instance> instance)
{
	if (!instance)
		return;
	destroyDebugUtils(instance);
	//destroyDebugReport(instance);
}

void DebugExtension::createDebugUtils(std::shared_ptr<const Instance> instance)
{
	VkDebugUtilsMessengerCreateInfoEXT callback = {};
	callback.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	callback.flags = 0;
	callback.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	switch (logLevel_)
	{
	case 4:
		callback.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
	case 3:
		callback.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
	case 2:
		callback.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
	case 1:
		callback.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	}
	auto logCallback = [](
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
		void *pUserData) -> VkBool32
	{
		auto *loggerTagged = (ILoggerTagged*)pUserData;
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
		}
		loggerTagged->log(level, pCallbackData->pMessage);
		return VK_FALSE;
	};
	callback.pfnUserCallback = logCallback;
	callback.pUserData = (void *) &(*loggerTagged_);
	data_->createDebugUtils(instance->getInstance(), &callback, nullptr, &data_->messeger);
}

void DebugExtension::destroyDebugUtils(std::shared_ptr<const Instance> instance)
{
	data_->destroyDebugUtils(instance->getInstance(), data_->messeger, nullptr);
	data_->messeger = {};
}

void DebugExtension::createDebugReport(std::shared_ptr<const Instance> instance)
{
	VkDebugReportCallbackCreateInfoEXT reportInfo = {};
	reportInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	switch (logLevel_)
	{
	case 4:
		reportInfo.flags |= VK_DEBUG_REPORT_DEBUG_BIT_EXT;
	case 3:
		reportInfo.flags |= VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
	case 2:
		reportInfo.flags |= VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
	case 1:
		reportInfo.flags |= VK_DEBUG_REPORT_ERROR_BIT_EXT;
	}
	auto logCallback = [](
		VkDebugReportFlagsEXT                       flags,
		VkDebugReportObjectTypeEXT                  objectType,
		uint64_t                                    object,
		size_t                                      location,
		int32_t                                     messageCode,
		const char*                                 pLayerPrefix,
		const char*                                 pMessage,
		void*                                       pUserData) -> VkBool32
	{
		auto *loggerTagged = (ILoggerTagged*)pUserData;
		LogLevel level;
		switch (flags)
		{
		case VK_DEBUG_REPORT_ERROR_BIT_EXT:
			level = LogLevel::Error;
			break;
		case VK_DEBUG_REPORT_WARNING_BIT_EXT:
			level = LogLevel::Warning;
			break;
		case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
			level = LogLevel::Info;
			break;
		case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
			level = LogLevel::Debug;
			break;
		case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
			level = LogLevel::Warning;
			break;
		}
		loggerTagged->log(level, "{" + std::string(pLayerPrefix) + "} "+ pMessage);
		return VK_FALSE;
	};
	reportInfo.pfnCallback = logCallback;
	reportInfo.pUserData = (void *) &(*loggerTagged_);
	data_->createDebugReportCallback(instance->getInstance(), &reportInfo, nullptr, &data_->callback);
}

void DebugExtension::destroyDebugReport(std::shared_ptr<const Instance> instance)
{
	data_->destroyDebugReportCallback(instance->getInstance(), data_->callback, nullptr);
	data_->callback = {};
}

void DebugExtension::added(InstanceBuilder &builder)
{

}

void DebugExtension::fillFunctionPointers(std::shared_ptr<const Instance> instance)
{
	auto vkInstance = instance->getInstance();
	data_->createDebugUtils = getVkFuncInstancePtr(vkInstance, vkCreateDebugUtilsMessengerEXT);
	data_->destroyDebugUtils = getVkFuncInstancePtr(vkInstance, vkDestroyDebugUtilsMessengerEXT);
	data_->createDebugReportCallback = getVkFuncInstancePtr(vkInstance, vkCreateDebugReportCallbackEXT);
	data_->destroyDebugReportCallback = getVkFuncInstancePtr(vkInstance, vkDestroyDebugReportCallbackEXT);
}
