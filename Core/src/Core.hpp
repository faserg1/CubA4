#pragma once

#include <memory>
#include <ICore.hpp>
#include <CoreExportHelper.hpp>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			class CoreConfig;
		}

		namespace system
		{
			class IAppCallback;
		}

		class Core final :
			public virtual ICore, public std::enable_shared_from_this<Core>
		{
		public:
			explicit Core(int argc, const char *const argv[]);
			~Core();

			const std::shared_ptr<const config::IFilePaths> getPaths() const override;
			std::shared_ptr<config::ICoreConfig> getConfig() const override;
			std::shared_ptr<logging::ILogger> getLogger() const override;
			std::shared_ptr<model::IModelReader> getModelReader() const override;
			std::shared_ptr<const resources::IResourcesManager> getResourcesManager() const override;
			std::shared_ptr<system::IRuntime> getRuntime() override;

			void criticalException() const override;
		protected:
		private:
			const std::shared_ptr<const config::IFilePaths> paths_;
			std::shared_ptr<config::CoreConfig> config_;
			std::shared_ptr<logging::ILogger> logger_;
			std::shared_ptr<model::IModelReader> modelReader_;
			std::shared_ptr<resources::IResourcesManager> resourceManager_;
			std::shared_ptr<system::IRuntime> runtime_;

			std::shared_ptr<system::IStartup> startup_;
		};
	}
}