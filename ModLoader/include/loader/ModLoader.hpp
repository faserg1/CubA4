#ifndef LOADER_MOD_LOADER
#define LOADER_MOD_LOADER

#include <memory>
#include <vector>
#include <ModLoaderLibrary.hpp>
#include <mod/IModLoader.hpp>

namespace CubA4
{
	namespace core
	{
		class ICore;
	}

	namespace mod
	{
		class ModLibrary;

		class MOD_LOADER_SHARED ModLoader : 
			public virtual IModLoader
		{
		public:
			ModLoader(std::shared_ptr<const core::ICore> core);
			virtual ~ModLoader();

			void find() override;
			void load() override;
			void setup() override;
			void unload() override;
		private:
			const std::shared_ptr<const core::ICore> core_;
			std::vector<std::string> candidates_;
			std::vector<std::shared_ptr<ModLibrary>> mods_;
		};
	}
}

#endif