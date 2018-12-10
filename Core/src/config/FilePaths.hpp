#ifndef CORE_FILEPATHS_HPP
#define CORE_FILEPATHS_HPP

#include <config/IFilePaths.hpp>
#include <boost/filesystem.hpp>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			class FilePaths :
				public IFilePaths
			{
			public:
				explicit FilePaths(int argc, const char *const argv[]);
				~FilePaths();

				std::string configPath() const override;
				std::string modsPath() const override;
				std::string renderPath() const override;
				std::string logsPath() const override;
			protected:
			private:
				boost::filesystem::path initialPath_;
			};
		}
	}
}

#endif // CORE_FILEPATHS_HPP
