#ifndef MOD_LIBRARY_HPP
#define MOD_LIBRARY_HPP

#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

namespace CubA4
{
	namespace mod
	{
		class ModInfo;
	}

	namespace loader
	{
		class ModLibrary
		{
			const char *importSymbolName_;
			boost::dll::shared_library library_;
			CubA4::mod::ModInfo *modInfo_;
			bool validLibrary_;
		public:
			ModLibrary(boost::filesystem::path path);
			bool isValidLibrary();
		};
	}
}

#endif // MOD_LIBRARY_HPP