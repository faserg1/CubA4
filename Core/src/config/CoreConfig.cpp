#include "CoreConfig.hpp"

#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using namespace CubA4::config;

constexpr const char *mainFeatiresModIdKey = "core.mods.main_features_mod_id";
constexpr const char *worldChunkSizeKey = "core.world.chunk_size";

CoreConfig::CoreConfig(std::string configsPath)
{
	auto configPathsDirectory = std::filesystem::path(configsPath);
	auto configPath = configPathsDirectory / "core.json";

	if (!std::filesystem::exists(configPathsDirectory))
	{
		std::filesystem::create_directory(configPathsDirectory);
	}
	else if (!std::filesystem::is_directory(configPathsDirectory))
	{
		throw std::runtime_error("`config` is not a directory!");
	}

	native_config_path_ = configPath.string();
	configTree_ = std::make_shared<CoreData>();
	if (std::filesystem::exists(configPath))
		reload();
}

CoreConfig::~CoreConfig()
{
	
}

std::string CoreConfig::getRenderEngineId() const
{
	return configTree_->render.engine;
}

void CoreConfig::setRenderEngineId(const std::string &renderEngineId)
{
	configTree_->render.engine = renderEngineId;
	flushConfig();
}

std::string CoreConfig::getMainFeatiresModId() const
{
	return configTree_->mods.mainMod;
}

void CoreConfig::setMainFeaturesModId(const std::string &modId)
{
	configTree_->mods.mainMod = modId;
	flushConfig();
}

unsigned short CoreConfig::getWorldChunkSize()
{
	return configTree_->world.chunkSize;
}

void CoreConfig::setWorldChunkSize(unsigned short size)
{
	configTree_->world.chunkSize = size;
	flushConfig();
}

void CoreConfig::reload()
{
	std::ifstream file(native_config_path_);
	*configTree_ = nlohmann::json::parse(file);
}

void CoreConfig::flushConfig()
{
	std::ofstream file(native_config_path_);
	nlohmann::json j = *configTree_;
	file << j.dump(1, '\t');
}

