#ifndef ICORE_HPP
#define ICORE_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			class IFilePaths;
			class ICoreConfig;
		}

		namespace logging
		{
			class ILogger;
		}

		class ICore
		{
		public:
			virtual const std::shared_ptr<const config::IFilePaths> getPaths() const = 0;
			virtual std::shared_ptr<config::ICoreConfig> getConfig() const = 0;
			virtual std::shared_ptr<logging::ILogger> getLogger() const = 0;

			virtual ~ICore() {}
		protected:
			explicit ICore() {}
		};
	}
}

#endif // ICORE_HPP