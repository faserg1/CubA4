#ifndef RENDERVULKAN_DEBUGEXTENSION_HPP
#define RENDERVULKAN_DEBUGEXTENSION_HPP

#include "InstanceExtension.hpp"
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
				struct DebugExtensionData;

				class DebugExtension :
					public InstanceExtension
				{
				public:
					explicit DebugExtension(std::shared_ptr<core::logging::ILogger> logger);
					~DebugExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const Instance> instance) override;
					void destroy(std::shared_ptr<const Instance> instance) override;
					void added(InstanceBuilder &builder) override;
				protected:
					void createDebugUtils(std::shared_ptr<const Instance> instance);
					void destroyDebugUtils(std::shared_ptr<const Instance> instance);

					void createDebugReport(std::shared_ptr<const Instance> instance);
					void destroyDebugReport(std::shared_ptr<const Instance> instance);
				private:
					void fillFunctionPointers(std::shared_ptr<const Instance> instance);

					std::shared_ptr<DebugExtensionData> data_;
					std::shared_ptr<core::logging::ILoggerTagged> loggerTagged_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_DEBUGEXTENSION_HPP
