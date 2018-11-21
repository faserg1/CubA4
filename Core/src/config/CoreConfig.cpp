#include "CoreConfig.hpp"

#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

using namespace CubA4::core::config;

constexpr const char *renderEngineIdKey = "core.render.engine_id";
constexpr const char *mainFeatiresModIdKey = "core.mods.main_features_mod_id";
constexpr const char *worldChunkSizeKey = "core.world.chunk_size";

CoreConfig::CoreConfig(std::string configsPath)
{
	auto configPathsDirectory = boost::filesystem::path(configsPath);
	auto configPath = configPathsDirectory / "core.json";

	if (!boost::filesystem::exists(configPathsDirectory))
	{
		boost::filesystem::create_directory(configPathsDirectory);
	}
	else if (!boost::filesystem::is_directory(configPathsDirectory))
	{
		throw std::runtime_error("`config` is not a directory!");
	}

	native_config_path_ = configPath.string();
	configTree_ = std::make_shared<boost::property_tree::ptree>();
	if (boost::filesystem::exists(configPath))
		reload();
}

CoreConfig::~CoreConfig()
{
	
}

std::string CoreConfig::getRenderEngineId() const
{
	return configTree_->get<std::string>(renderEngineIdKey, "");
}

void CoreConfig::setRenderEngineId(const std::string &renderEngineId)
{
	configTree_->put(renderEngineIdKey, renderEngineId);
	flushConfig();
}

std::string CoreConfig::getMainFeatiresModId() const
{
	return configTree_->get<std::string>(mainFeatiresModIdKey, "");
}

void CoreConfig::setMainFeaturesModId(const std::string &modId)
{
	configTree_->put(mainFeatiresModIdKey, modId);
	flushConfig();
}

unsigned short CoreConfig::getWorldChunkSize()
{
	return configTree_->get<unsigned short>(worldChunkSizeKey, 0);
}

void CoreConfig::setWorldChunkSize(unsigned short size)
{
	configTree_->put(worldChunkSizeKey, size);
	flushConfig();
}

void CoreConfig::reload()
{
	boost::property_tree::json_parser::read_json(native_config_path_, *configTree_);
}

void CoreConfig::flushConfig()
{
	boost::property_tree::json_parser::write_json(native_config_path_, *configTree_);
}

