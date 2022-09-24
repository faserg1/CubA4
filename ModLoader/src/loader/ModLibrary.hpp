#ifndef MODLOADER_MOD_LIBRARY_HPP
#define MODLOADER_MOD_LIBRARY_HPP

#include <filesystem>
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
			ModLibrary(std::filesystem::path path);
			bool isValidLibrary() const;
			std::shared_ptr<const CubA4::mod::IModInfo> getModInfo() const;
			void destroy();
		private:
			const char *importSymbolName_;
			boost::dll::shared_library library_;
			std::shared_ptr<CubA4::mod::IModInfo> modInfo_;
			bool validLibrary_;
		};
	}
}

#endif // MODLOADER_MOD_LIBRARY_HPP