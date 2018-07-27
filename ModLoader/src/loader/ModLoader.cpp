#include <loader/ModLoader.hpp>
#include "ModLibrary.hpp"
#include <ICore.hpp>
#include <config/IFilePaths.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>

#include <vector>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/dll.hpp>

using namespace CubA4::mod;
using namespace CubA4::core;
using namespace CubA4::core::config;
using namespace CubA4::core::logging;

ModLoader::ModLoader(std::shared_ptr<const ICore> core) :
	core_(core)
{
	log_ = std::shared_ptr<CubA4::core::logging::ILoggerTagged>(core_->getLogger()->createTaggedLog(LogSourceSystem::Mod, "LOADER"));
}

ModLoader::~ModLoader()
{
	
}

void ModLoader::find()
{
	auto modsPath = core_->getPaths()->modsPath();
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
		log_->log(LogLevel::Info, "Find mod candidate: " + path.generic_string());
	}
}

void ModLoader::load()
{
	using namespace boost::filesystem;
	for (auto candidate : candidates_)
	{
		auto library = std::make_shared<ModLibrary>(path(candidate));
		if (library->isValidLibrary())
			mods_.push_back(library);
		else
			log_->log(LogLevel::Warning, "Invalid mod library: " + candidate);
	}
}

void ModLoader::setup()
{

}

void ModLoader::unload()
{

}