#ifndef COREBASE_IFILEPATHS_HPP
#define COREBASE_IFILEPATHS_HPP

#include <string>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			class IFilePaths
			{
			public:
				virtual std::string configPath() const = 0;
				virtual std::string modsPath() const = 0;
				virtual std::string renderPath() const = 0;
				virtual std::string logsPath() const = 0;
				virtual std::string cachePath() const = 0;
				virtual std::string resourcesPath() const = 0;
			protected:
				explicit IFilePaths() = default;
				virtual ~IFilePaths() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IFILEPATHS_HPP
