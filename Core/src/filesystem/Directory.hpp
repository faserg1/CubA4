#ifndef CORE_DIRECTORY_HPP
#define CORE_DIRECTORY_HPP

#include <filesystem/IAbstractDirectory.hpp>
#include <boost/filesystem.hpp>

namespace CubA4
{
	namespace core
	{
		namespace filesystem
		{
			class Directory :
				public virtual IAbstractDirectory
			{
			public:
				explicit Directory(boost::filesystem::path path, bool createIfNotExists);
				~Directory();
				
				bool exists(std::string path) const override;
				bool isDirectory(std::string path) const override;
				bool isFile(std::string path) const override;
				std::vector<std::string> listDirectories() const override;
				std::vector<std::string> listFiles() const override;
			protected:
			private:
				const boost::filesystem::path path_;
			};
		}
	}
}

#endif // CORE_DIRECTORY_HPP
