#ifndef COREBASE_IABSTRACTDIRECTORY_HPP
#define COREBASE_IABSTRACTDIRECTORY_HPP

#include <vector>
#include <string>

namespace CubA4
{
	namespace core
	{
		namespace filesystem
		{
			class IAbstractDirectory
			{
			public:
				virtual bool exists(std::string path) const = 0;
				virtual bool isDirectory(std::string path) const = 0;
				virtual bool isFile(std::string path) const = 0;
				virtual std::vector<std::string> listDirectories() const = 0;
				virtual std::vector<std::string> listFiles() const = 0;
			protected:
				explicit IAbstractDirectory() = default;
				virtual ~IAbstractDirectory() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IABSTRACTDIRECTORY_HPP
