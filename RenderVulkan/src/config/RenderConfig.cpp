#include "./RenderConfig.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>
using namespace CubA4::render::config;

constexpr const char *renderResolutionWidthKey = "render.resolution.width";
constexpr const char *renderResolutionHeightKey = "render.resolution.height";

constexpr const char *renderPresentMethodKey = "render.present.method";

constexpr const char *renderLoggingLevel = "render.log.level";

RenderConfig::RenderConfig(std::string configsPath)
{
	auto configPathsDirectory = boost::filesystem::path(configsPath);
	auto configPath = configPathsDirectory / "renderVulkan.json";

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

RenderConfig::~RenderConfig()
{
	
}

std::tuple<unsigned, unsigned> RenderConfig::getRenderResolution(std::tuple<unsigned, unsigned> defaultResolution) const
{
	unsigned width = configTree_->get<unsigned>(renderResolutionWidthKey, std::get<0>(defaultResolution));
	unsigned height = configTree_->get<unsigned>(renderResolutionHeightKey, std::get<1>(defaultResolution));
	return std::make_tuple(width, height);
}

void RenderConfig::setRenderResolution(std::tuple<unsigned, unsigned> res)
{
	configTree_->put(renderResolutionWidthKey, std::get<0>(res));
	configTree_->put(renderResolutionHeightKey, std::get<1>(res));
	flushConfig();
}

std::string RenderConfig::getPresentMethod(std::string methodByDefault) const
{
	return configTree_->get<std::string>(renderPresentMethodKey, methodByDefault);
}

void RenderConfig::setPresentMethod(std::string method)
{
	configTree_->put(renderPresentMethodKey, method);
	flushConfig();
}

int RenderConfig::getLoggingLevel(int lvl) const
{
	return configTree_->get<int>(renderLoggingLevel, lvl);
}

void RenderConfig::setLoggingLevel(int lvl)
{
	configTree_->put(renderLoggingLevel, lvl);
	flushConfig();
}

void RenderConfig::reload()
{
	boost::property_tree::json_parser::read_json(native_config_path_, *configTree_);
}

void RenderConfig::flushConfig()
{
	boost::property_tree::json_parser::write_json(native_config_path_, *configTree_);
}
