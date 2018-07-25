#ifndef MOD_LIBRARY_HPP
#define MOD_LIBRARY_HPP

#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
#include <memory>

namespace CubA4
{
	namespace mod
	{
		class IModInfo;

		class ModLibrary
		{
		public:
			ModLibrary(boost::filesystem::path path);
			bool isValidLibrary() const;
			std::shared_ptr<const CubA4::mod::IModInfo> getModInfo() const;
		private:
			const char *importSymbolName_;
			boost::dll::shared_library library_;
			std::shared_ptr<CubA4::mod::IModInfo> modInfo_;
			bool validLibrary_;
		};
	}
}

#endif // MOD_LIBRARY_HPP