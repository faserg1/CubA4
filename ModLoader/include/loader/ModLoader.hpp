#ifndef LOADER_MOD_LOADER
#define LOADER_MOD_LOADER

#include <ModLoaderLibrary.hpp>
#include <memory>

namespace CubA4
{
	namespace mod_loader
	{
		class MOD_LOADER_SHARED ModLoader
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