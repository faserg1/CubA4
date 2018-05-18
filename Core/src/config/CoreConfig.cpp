#include "../../include/config/CoreConfig.hpp"

#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

using namespace CubA4::core::config;

constexpr char *renderEngineIdKey = "core.render.engine_id";
constexpr char *mainFeatiresModIdKey = "core.mods.main_features_mod_id";
constexpr char *worldChunkSizeKey = "core.world.chunk_size";

CoreConfig::CoreConfig()
{
	auto configPathDirectory = boost::filesystem::current_path() / "config";
	auto configPath = configPathDirectory / "core.json";

	if (!boost::filesystem::exists(configPathDirectory))
	{
		boost::filesystem::create_directory(configPathDirectory);
	}
	else if (!boost::filesystem::is_directory(configPathDirectory))
	{
		throw std::runtime_error("`config` is not a directory!");
	}

	native_config_path_ = configPath.string();
	configTree_ = std::make_shared<boost::property_tree::ptree>(boost::property_tree::ptree());
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

