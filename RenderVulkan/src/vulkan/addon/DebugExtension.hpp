#pragma once

#include "InstanceExtension.hpp"
#include <logging/ILogger.hpp>
#include <memory>
#include <array>
#include <vulkan/vulkan.hpp>

namespace CubA4::render
{
	namespace config
	{
		class IRenderConfig;
	}

	namespace vulkan::addon
	{
		struct DebugExtensionData;

		class DebugExtension :
			public InstanceExtension
		{
		public:
			explicit DebugExtension(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<config::IRenderConfig> cfg);
			~DebugExtension();

			std::vector<std::string> names() const override;
			void init(std::shared_ptr<const Instance> instance) override;
			void destroy(std::shared_ptr<const Instance> instance) override;
			void added(InstanceBuilder &builder) override;
		protected:
			void createDebugUtils(std::shared_ptr<const Instance> instance);
			void destroyDebugUtils(std::shared_ptr<const Instance> instance);
		private:
			const std::shared_ptr<logging::ILoggerTagged> loggerTagged_;
			const std::shared_ptr<DebugExtensionData> data_;
			int logLevel_;
		private:
			void fillFunctionPointers(std::shared_ptr<const Instance> instance);
		};
	}
}

