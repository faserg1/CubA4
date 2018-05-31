#ifndef CORE_HPP
#define CORE_HPP

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
		

		class CORE_LIBRARY_EXPORT Core :
			public virtual ICore
		{
		public:
			explicit Core(int argc, const char *const argv[]);
			~Core();

			const std::shared_ptr<const config::IFilePaths> getPaths() const override;
			std::shared_ptr<config::ICoreConfig> getConfig() const override;
			std::shared_ptr<logging::ILogger> getLogger() const override;
		private:
			const std::shared_ptr<const config::IFilePaths> paths_;
			std::shared_ptr<config::CoreConfig> config_;
			std::shared_ptr<logging::ILogger> logger_;
		};
	}
}

#endif // CORE_HPP