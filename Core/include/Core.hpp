#ifndef CORE_CORE_HPP
#define CORE_CORE_HPP

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

		class CORE_LIBRARY_EXPORT Core :
			public virtual ICore
		{
		public:
			const std::shared_ptr<const config::IFilePaths> getPaths() const override;
			std::shared_ptr<config::ICoreConfig> getConfig() const override;
			std::shared_ptr<logging::ILogger> getLogger() const override;
			std::shared_ptr<resources::IResourcesManager> getResourcesManager() const override;
			std::shared_ptr<cache::ICacheManager> getCacheManager() const override;

			std::shared_ptr<system::IStartup> getStartup() override;

			static std::shared_ptr<ICore> create(int argc, const char *const argv[]);

			void criticalException() const override;
		protected:
			explicit Core(int argc, const char *const argv[]);
			~Core();
		private:
			const std::shared_ptr<const config::IFilePaths> paths_;
			std::shared_ptr<config::CoreConfig> config_;
			std::shared_ptr<logging::ILogger> logger_;

			std::shared_ptr<system::IStartup> startup_;

			///Слабый указатель на себя. Присваивается через create()
			std::weak_ptr<ICore> core_;
		};
	}
}

#endif // CORE_CORE_HPP