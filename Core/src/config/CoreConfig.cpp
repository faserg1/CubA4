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

std::string CoreConfig::checkFeatureModId(const std::string &feature) const
{
	auto it = configTree_->mods.overridedFeatures.find(feature);
	if (it == configTree_->mods.overridedFeatures.end())
		return configTree_->mods.mainMod;
	return it->second;
}

void CoreConfig::setFeatureModId(const std::string &feature, const std::string &modId)
{
	configTree_->mods.overridedFeatures.insert_or_assign(feature, modId);
}

void CoreConfig::setMainFeaturesModId(const std::string &modId)
{
	configTree_->mods.mainMod = modId;
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

