#include "./RenderConfig.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>
using namespace CubA4::render::config;

constexpr const char *renderResolutionWidthKey = "render.resolution.width";
constexpr const char *renderResolutionHeightKey = "render.resolution.height";

constexpr const char *renderPresentMethodKey = "render.present.method";

constexpr const char *renderLoggingLevel = "render.log.level";

RenderConfig::RenderConfig(std::string configsPath)
{
	auto configPathsDirectory = std::filesystem::path(configsPath);
	auto configPath = configPathsDirectory / "renderVulkan.json";

	if (!std::filesystem::exists(configPathsDirectory))
	{
		std::filesystem::create_directory(configPathsDirectory);
	}
	else if (!std::filesystem::is_directory(configPathsDirectory))
	{
		throw std::runtime_error("`config` is not a directory!");
	}

	native_config_path_ = configPath.string();
	configTree_ = std::make_shared<RenderData>();
	if (std::filesystem::exists(configPath))
		reload();
}

RenderConfig::~RenderConfig()
{
	
}

std::tuple<unsigned, unsigned> RenderConfig::getRenderResolution() const
{
	unsigned width = configTree_->presentation.width;
	unsigned height = configTree_->presentation.height;
	return std::make_tuple(width, height);
}

void RenderConfig::setRenderResolution(std::tuple<unsigned, unsigned> res)
{
	configTree_->presentation.width = std::get<0>(res);
	configTree_->presentation.height = std::get<1>(res);
	flushConfig();
}

std::string RenderConfig::getPresentMethod() const
{
	return configTree_->presentation.method;
}

void RenderConfig::setPresentMethod(std::string method)
{
	configTree_->presentation.method = method;
	flushConfig();
}

int RenderConfig::getLoggingLevel() const
{
	return configTree_->misc.logLevel;
}

void RenderConfig::setLoggingLevel(int lvl)
{
	configTree_->misc.logLevel = lvl;
	flushConfig();
}

AntiAliasing RenderConfig::getAntialiasing() const
{
	return static_cast<AntiAliasing>(configTree_->quality.antialiasing);
}

void RenderConfig::setAntialiasing(AntiAliasing lvl)
{
	configTree_->quality.antialiasing = static_cast<decltype(configTree_->quality.antialiasing)>(lvl);
	flushConfig();
}

void RenderConfig::reload()
{
	std::ifstream file(native_config_path_);
	*configTree_ = nlohmann::json::parse(file);
}

void RenderConfig::flushConfig()
{
	std::ofstream file(native_config_path_);
	nlohmann::json j = *configTree_;
	file << j.dump(1, '\t');
}
