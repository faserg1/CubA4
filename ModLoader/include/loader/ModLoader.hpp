#ifndef LOADER_MOD_LOADER
#define LOADER_MOD_LOADER

#include <ModLoaderLibrary.hpp>
#include <memory>
#include <mod/IModLoader.hpp>

namespace CubA4
{
	namespace mod_loader
	{
		class MOD_LOADER_SHARED ModLoader : 
			public virtual CubA4::mod::IModLoader
		{
			struct Private;
			std::shared_ptr<Private> data_;
		public:
			ModLoader();
			virtual ~ModLoader();
		};
	}
}

#endif