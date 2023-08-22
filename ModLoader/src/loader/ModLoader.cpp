#include <loader/ModLoader.hpp>
#include <loader/ModLibrary.hpp>

#include <ICore.hpp>
#include <config/IFilePaths.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>

#include <IModInfo.hpp>
#include <mod/IMod.hpp>

#include <info/IApplicationInfo.hpp>
#include <info/IVersionDependency.hpp>
#include <info/IVersion.hpp>

#include <mod/ModLinker.hpp>

#include <algorithm>
#include <vector>
#include <map>
#include <filesystem>
#include <boost/dll.hpp>

#include <fmt/format.h>

using namespace CubA4::mod;
using namespace CubA4::config;
using namespace CubA4::logging;

ModLoader::ModLoader(std::weak_ptr<const ICore> core, std::shared_ptr<const CubA4::info::IApplicationInfo> appInfo) :
	core_(core), appInfo_(appInfo)
{
	if (auto lockedCore = core_.lock())
	{
		log_ = lockedCore->getLogger()->createTaggedLog(LogSourceSystem::Mod, "LOADER");
	}
}

ModLoader::~ModLoader()
{
	unload();
}

void ModLoader::find()
{
	auto modsPath = core_.lock()->getPaths()->modsPath();
	using namespace std::filesystem;
	auto modsFolder = path(modsPath);
	recursive_directory_iterator modsFolderIterator(modsFolder), end;

	for (modsFolderIterator; modsFolderIterator != end; modsFolderIterator++)
	{
		auto path = modsFolderIterator->path();
		if (is_directory(path))
			continue;
		if (path.extension() != boost::dll::shared_library::suffix())
			continue;
		candidates_.push_back(path.generic_string());
		log_->log(LogLevel::Info, fmt::format("Find mod candidate: {}.", path.generic_string()));
	}
}

void ModLoader::load()
{
	using namespace std::filesystem;
	for (auto candidate : candidates_)
	{
		auto library = std::make_shared<ModLibrary>(path(candidate));
		if (library->isValidLibrary())
		{
			modLibs_.push_back(library);
			auto modInfo = library->getModInfo();
			log_->log(LogLevel::Info, fmt::format("Loaded mod: {}.", modInfo->getIdName()));
		}
		else
			log_->log(LogLevel::Warning, fmt::format("Invalid mod library: {}.", candidate));
	}
}

void ModLoader::setup(IEnvironmentBuilderFactory builderFactory)
{
	std::vector<std::shared_ptr<const IModInfo>> modInfos;
	std::vector<std::shared_ptr<IMod>> mods;
	log_->log(LogLevel::Info, "Checking for app dependency.");
	for (auto library : modLibs_)
	{
		auto modInfo = library->getModInfo();
		auto &appDep = modInfo->getAppDependency();
		if (appDep.required().major() != appInfo_->version().major())
		{
			log_->log(LogLevel::Warning, fmt::format("Skipping mod {}: Required app version is: {}, current: {}. Major version is not equal.",
				modInfo->getIdName(), appDep.required().to_string(), appInfo_->version().to_string()));
			continue;
		}
		if (appDep.required().minor() > appInfo_->version().minor())
		{
			log_->log(LogLevel::Warning, fmt::format("Skipping mod {}: Required app version is: {}, current: {}. Minor version is lower than required.",
				modInfo->getIdName(), appDep.required().to_string(), appInfo_->version().to_string()));
			continue;
		}
		modInfos.push_back(modInfo);
		//TODO: [OOKAMI] Check prefered deps
	}
	log_->log(LogLevel::Info, "Checking for mod dependency.");

	std::vector<std::shared_ptr<const IModInfo>> depsCheckedMods;
	// Key: depended on, Value: mods depended on Id (key)
	std::map<std::string, std::vector<std::shared_ptr<const IModInfo>>> mapDeps;
	// TODO: What about recursive deps?
	for (auto modInfo : modInfos)
	{
		auto reqs = modInfo->getRequiredMods();
		if (reqs.empty())
		{
			depsCheckedMods.push_back(modInfo);
			continue;
		}
		for (auto reqMod : reqs)
		{
			auto modRequired = std::find_if(modInfos.begin(), modInfos.end(), [currentModInfo = modInfo, reqMod, this](std::shared_ptr<const IModInfo> modInfo) -> bool
			{
				if (modInfo->getIdName() != reqMod)
					return false;
				auto &verDep = currentModInfo->getModDependency(reqMod);
				if (verDep.required().major() > modInfo->getVersion().major() ||
					verDep.required().minor() > modInfo->getVersion().minor() ||
					verDep.required().patch() > modInfo->getVersion().patch())
				{
					log_->log(LogLevel::Warning, fmt::format("Skipping mod {}: Required mod {} version is: {}, current: {}.",
						currentModInfo->getIdName(), modInfo->getIdName(), verDep.required().to_string(), modInfo->getVersion().to_string()));
					return false;
				}
				return true;
			});
			// Required mod not found
			if (modRequired == modInfos.end())
			{
				std::vector<std::string> brokenModIdList{ modInfo->getIdName() };
				while (!brokenModIdList.empty())
				{
					auto brokenModIdListCopy = brokenModIdList;
					for (auto brokenModId : brokenModIdListCopy)
					{
						auto brokenModsIter = mapDeps.find(brokenModId);
						if (brokenModsIter == mapDeps.end())
							continue;
						auto brokenMods = brokenModsIter->second;
						std::transform(brokenMods.begin(), brokenMods.end(), back_inserter(brokenModIdList), [](std::shared_ptr<const IModInfo> modInfo) -> std::string
						{
							return modInfo->getIdName();
						});
						for (auto mod : brokenMods)
						{
							auto it = std::remove(depsCheckedMods.begin(), depsCheckedMods.end(), mod);
							depsCheckedMods.erase(it, depsCheckedMods.end());
						}
					}
				}
				continue;
			}
			depsCheckedMods.push_back(modInfo);
			if (mapDeps.find(reqMod) == mapDeps.end())
				mapDeps.insert(std::make_pair(reqMod, std::vector<std::shared_ptr<const IModInfo>> {}));
			mapDeps.find(reqMod)->second.push_back(modInfo);
		}
	}
	for (auto modInfo : depsCheckedMods)
	{
		auto mod = modInfo->createMod();

		if (mod)
			mods.push_back(mod);
		else
			log_->log(LogLevel::Info, fmt::format("The %1% is meta mod. Skipping next steps for this mod", modInfo->getIdName()));
	}
	setupModByChain(builderFactory, mods);
}

void ModLoader::finished()
{
	for (auto mod : loadedMods_)
	{
		mod->finish();
	}
}

void ModLoader::setupModByChain(IEnvironmentBuilderFactory builderFactory, std::vector<std::shared_ptr<IMod>> mods)
{
	std::map<std::string, std::shared_ptr<CubA4::core::IEnvironmentBuilder>> builders;
	auto core = core_.lock();
	log_->log(LogLevel::Info, "Loading mods.");
	for (auto mod : mods)
	{
		mod->load(core);
	}
	log_->log(LogLevel::Info, "Preiniting mods.");
	for (auto mod : mods)
	{
		auto builder = builderFactory(mod->getInfo());
		builders.insert(std::make_pair(mod->getInfo().getIdName(), builder));
		mod->preinit(builder);
	}
	log_->log(LogLevel::Info, "Linking mods.");
	{
		auto linker = ModLinker(mods);
		for (auto mod : mods)
		{
			mod->link(linker);
		}
	}
	
	log_->log(LogLevel::Info, "Initing mods.");
	for (auto mod : mods)
	{
		auto builder = builders.find(mod->getInfo().getIdName())->second;
		mod->init(builder);
	}
	log_->log(LogLevel::Info, "Configuring mods.");
	for (auto mod : mods)
	{
		auto builder = builders.find(mod->getInfo().getIdName())->second;
		mod->configure(builder);
	}
	log_->log(LogLevel::Info, "Finishing load mods.");
	for (auto mod : mods)
	{
		auto builder = builders.find(mod->getInfo().getIdName())->second;
		loadedMods_.push_back(mod);
		mod->prefinish(builder);
	}
}

void ModLoader::shutdown()
{
	for (auto mod : loadedMods_)
	{
		mod->preunload();
	}
	loadedMods_.clear();
	for (auto library : modLibs_)
	{
		library->destroy();
	}
}

void ModLoader::unload()
{
	modLibs_.clear();
}

void ModLoader::start(CubA4::game::IGameControl &gameControl)
{
	for (auto mod : loadedMods_)
	{
		mod->start(gameControl);
	}
}

void ModLoader::stop()
{
	for (auto mod : loadedMods_)
	{
		mod->stop();
	}
}