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
			explicit Core();
			~Core();

			std::shared_ptr<config::ICoreConfig> getConfig() override;
			std::shared_ptr<const config::IFilePaths> getPaths() override;
		private:
			std::shared_ptr<config::CoreConfig> config_;
		};
	}
}

#endif // CORE_HPP