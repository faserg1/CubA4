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

		class ICore
		{
		public:
			virtual std::shared_ptr<config::ICoreConfig> getConfig() = 0;
			virtual std::shared_ptr<const config::IFilePaths> getPaths() = 0;

			virtual ~ICore() {}
		protected:
			explicit ICore() {}
		};
	}
}

#endif // ICORE_HPP