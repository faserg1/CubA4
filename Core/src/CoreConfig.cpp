#include "../include/CoreConfig.hpp"

#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

using namespace CubA4::core;

constexpr char *renderEngineIdKey = "core.render.engine_id";
constexpr char *mainFeatiresModId = "core.mods.main_features_mod_id";

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
	return configTree_->get<std::string>(mainFeatiresModId, "");
}

void CoreConfig::setMainFeaturesModId(const std::string &modId)
{
	configTree_->put(mainFeatiresModId, modId);
	flushConfig();
}

void CoreConfig::reload()
{
	boost::property_tree::json_parser::read_json(native_config_path_, *configTree_);
}

void CubA4::core::CoreConfig::flushConfig()
{
	boost::property_tree::json_parser::write_json(native_config_path_, *configTree_);
}

