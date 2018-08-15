#ifndef IFILEPATHS_HPP
#define IFILEPATHS_HPP

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
			protected:
				explicit IFilePaths() = default;
				virtual ~IFilePaths() = default;
			private:
			};
		}
	}
}

#endif // IFILEPATHS_HPP
