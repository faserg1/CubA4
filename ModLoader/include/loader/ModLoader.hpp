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

		namespace logging
		{
			class ILoggerTagged;
		}

		namespace info
		{
			class IApplicationInfo;
		}
	}

	namespace mod
	{
		class ModLibrary;
		class IMod;

		class MOD_LOADER_SHARED ModLoader : 
			public virtual IModLoader
		{
		public:
			ModLoader(std::weak_ptr<const core::ICore> core, std::shared_ptr<const core::info::IApplicationInfo> appInfo);
			virtual ~ModLoader();

			void find() override;
			void load() override;
			void setup(IEnvironmentBuilderFactory builderFactory) override;
			void unload() override;
		private:
			const std::weak_ptr<const core::ICore> core_;
			const std::shared_ptr<const core::info::IApplicationInfo> appInfo_;
			std::vector<std::string> candidates_;
			std::vector<std::shared_ptr<ModLibrary>> modLibs_;
			std::shared_ptr<core::logging::ILoggerTagged> log_;
			std::vector<std::shared_ptr<IMod>> loadedMods_;
		};
	}
}

#endif