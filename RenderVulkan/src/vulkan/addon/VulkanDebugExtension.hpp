#ifndef VULKANDEBUGEXTENSION_HPP
#define VULKANDEBUGEXTENSION_HPP

#include "VulkanExtension.hpp"

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
				class VulkanDebugExtension :
					public VulkanExtension
				{
				public:
					explicit VulkanDebugExtension(std::shared_ptr<core::logging::ILogger> logger);
					~VulkanDebugExtension();

					std::vector<std::string> names() const;
					void init(std::shared_ptr<VulkanInstance> instance);
					void destroy(std::shared_ptr<VulkanInstance> instance);
				protected:
				private:
					std::shared_ptr<core::logging::ILoggerTagged> loggerTagged_;
				};
			}
		}
	}
}

#endif // VULKANDEBUGEXTENSION_HPP
