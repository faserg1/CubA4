#ifndef LOADER_MOD_LOADER
#define LOADER_MOD_LOADER

#include <ModLoaderLibrary.hpp>
#include <memory>
#include <mod/IModLoader.hpp>

namespace CubA4
{
	namespace core
	{
		class ICore;
	}

	namespace mod_loader
	{
		class MOD_LOADER_SHARED ModLoader : 
			public virtual CubA4::mod::IModLoader
		{
		public:
			ModLoader(std::shared_ptr<const core::ICore> core);
			virtual ~ModLoader();
		private:
			const std::shared_ptr<const core::ICore> core_;
		};
	}
}

#endif