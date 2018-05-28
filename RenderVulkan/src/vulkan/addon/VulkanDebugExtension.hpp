#ifndef VULKANDEBUGEXTENSION_HPP
#define VULKANDEBUGEXTENSION_HPP

#include "VulkanInstanceExtension.hpp"
#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class ILogger;
			class ILoggerTagged;
		}
	}
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanDebugExtensionData;

				class VulkanDebugExtension :
					public VulkanInstanceExtension
				{
				public:
					explicit VulkanDebugExtension(std::shared_ptr<core::logging::ILogger> logger);
					~VulkanDebugExtension();

					std::vector<std::string> names() const;
					void init(std::shared_ptr<const VulkanInstance> instance);
					void destroy(std::shared_ptr<const VulkanInstance> instance);
				protected:
				private:
					void fillFunctionPointers(std::shared_ptr<const VulkanInstance> instance);

					std::shared_ptr<VulkanDebugExtensionData> data_;
					std::shared_ptr<core::logging::ILoggerTagged> loggerTagged_;
				};
			}
		}
	}
}

#endif // VULKANDEBUGEXTENSION_HPP
