#pragma once

#include <memory>
#include <vector>
#include <ModLoaderLibrary.hpp>
#include <mod/IModLoader.hpp>
#include <info/IApplicationInfo.hpp>

namespace CubA4::mod
{
	class ModLibrary;
	class IMod;

	class MOD_LOADER_SHARED ModLoader : 
		public virtual IModLoader
	{
	public:
		ModLoader(std::weak_ptr<const ICore> core, std::shared_ptr<const info::IApplicationInfo> appInfo);
		virtual ~ModLoader();

		void find() override;
		void load() override;
		void setup(IEnvironmentBuilderFactory builderFactory) override;
		void finished() override;
		void shutdown() override;
		void unload() override;

		void start(CubA4::game::IGameControl &gameControl) override;
		void stop() override;
	private:
		const std::weak_ptr<const ICore> core_;
		const std::shared_ptr<const info::IApplicationInfo> appInfo_;
		std::vector<std::string> candidates_;
		std::vector<std::shared_ptr<ModLibrary>> modLibs_;
		std::shared_ptr<logging::ILoggerTagged> log_;
		std::vector<std::shared_ptr<IMod>> loadedMods_;
	private:
		void setupModByChain(IEnvironmentBuilderFactory builderFactory, std::vector<std::shared_ptr<IMod>> mods);
	};
}
