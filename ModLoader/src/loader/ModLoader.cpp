#include <loader/ModLoader.hpp>
#include "ModLibrary.hpp"

#include <ICore.hpp>
#include <config/IFilePaths.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>

#include <IModInfo.hpp>
#include <mod/IMod.hpp>

#include <info/IApplicationInfo.hpp>
#include <info/IVersionDependency.hpp>
#include <info/IVersion.hpp>

#include <vector>
#include <map>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/dll.hpp>

#include <boost/format.hpp>

using namespace CubA4::mod;
using namespace CubA4::core;
using namespace CubA4::core::config;
using namespace CubA4::core::logging;

ModLoader::ModLoader(std::weak_ptr<const ICore> core, std::shared_ptr<const CubA4::core::info::IApplicationInfo> appInfo) :
	core_(core), appInfo_(appInfo)
{
	if (auto lockedCore = core_.lock())
	{
		log_ = std::shared_ptr<CubA4::core::logging::ILoggerTagged>(lockedCore->getLogger()->createTaggedLog(LogSourceSystem::Mod, "LOADER"));
	}
}

ModLoader::~ModLoader()
{
	
}

void ModLoader::find()
{
	auto modsPath = core_.lock()->getPaths()->modsPath();
	using namespace boost::filesystem;
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
		log_->log(LogLevel::Info, str(boost::format("Find mod candidate: %1%.") % path.generic_string()));
	}
}

void ModLoader::load()
{
	using namespace boost::filesystem;
	for (auto candidate : candidates_)
	{
		auto library = std::make_shared<ModLibrary>(path(candidate));
		if (library->isValidLibrary())
		{
			modLibs_.push_back(library);
			auto modInfo = library->getModInfo();
			log_->log(LogLevel::Info, str(boost::format("Loaded mod: %1%.") % modInfo->getIdName()));
		}
		else
			log_->log(LogLevel::Warning, str(boost::format("Invalid mod library: %1%.") % candidate));
	}
}

void ModLoader::setup()
{
	std::map<std::string, std::shared_ptr<const IModInfo>> modInfos;
	std::vector<std::shared_ptr<IMod>> mods;
	log_->log(LogLevel::Info, "Checking for app dependency.");
	for (auto library : modLibs_)
	{
		auto modInfo = library->getModInfo();
		auto &appDep = modInfo->getAppDependency();
		if (appDep.required().major() != appInfo_->version().major())
		{
			log_->log(LogLevel::Warning, str(boost::format("Skipping mod %1%: Required app version is: %2%, current: %3%. Major version is not equal.")
				% modInfo->getIdName() % appDep.required().to_string() % appInfo_->version().to_string()));
			continue;
		}
		if (appDep.required().minor() > appInfo_->version().minor())
		{
			log_->log(LogLevel::Warning, str(boost::format("Skipping mod %1%: Required app version is: %2%, current: %3%. Minor version is lower than required.")
				% modInfo->getIdName() % appDep.required().to_string() % appInfo_->version().to_string()));
			continue;
		}
		modInfos.insert(std::make_pair(modInfo->getIdName(), modInfo));
		//TODO: [OOKAMI] Check prefered deps
	}
	log_->log(LogLevel::Info, "Checking for mod dependency.");
	for (auto modInfoPair : modInfos)
	{
		//TODO: [OOKAMI] Check for mod deps
		auto mod = modInfoPair.second->getMod();
		if (mod)
			mods.push_back(mod);
		else
		{
			log_->log(LogLevel::Info, str(boost::format("The %1% is meta mod. Skipping next steps for this mod") % modInfoPair.first));
		}
	}
	log_->log(LogLevel::Info, "Loading mods.");
	for (auto mod : mods)
	{
		mod->load(core_.lock());
	}
	log_->log(LogLevel::Info, "Preiniting mods.");
	for (auto mod : mods)
	{
		mod->preinit();
	}
	log_->log(LogLevel::Info, "Linking mods.");
	for (auto mod : mods)
	{
		//TODO:: Place linker
		mod->link(nullptr);
	}
	log_->log(LogLevel::Info, "Initing mods.");
	for (auto mod : mods)
	{
		mod->init();
	}
	log_->log(LogLevel::Info, "Configuring mods.");
	for (auto mod : mods)
	{
		mod->configure();
	}
	log_->log(LogLevel::Info, "Finishing load mods.");
	for (auto mod : mods)
	{
		mod->done();
	}
}

void ModLoader::unload()
{
	for (auto mod : loadedMods_)
	{
		mod->preunload();
	}
	modLibs_.clear();
}