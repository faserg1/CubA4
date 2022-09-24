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
	configTree_ = std::make_shared<nlohmann::json>();
	if (std::filesystem::exists(configPath))
		reload();
}

RenderConfig::~RenderConfig()
{
	
}

std::tuple<unsigned, unsigned> RenderConfig::getRenderResolution(std::tuple<unsigned, unsigned> defaultResolution) const
{

	unsigned width = configTree_->at(renderResolutionWidthKey).get<unsigned>();
	unsigned height = configTree_->at(renderResolutionHeightKey).get<unsigned>();
	return std::make_tuple(width, height);
}

void RenderConfig::setRenderResolution(std::tuple<unsigned, unsigned> res)
{
	/*configTree_->put(renderResolutionWidthKey, std::get<0>(res));
	configTree_->put(renderResolutionHeightKey, std::get<1>(res));*/
	flushConfig();
}

std::string RenderConfig::getPresentMethod(std::string methodByDefault) const
{
	//return configTree_->get<std::string>(renderPresentMethodKey, methodByDefault);
	return {};
}

void RenderConfig::setPresentMethod(std::string method)
{
	//configTree_->put(renderPresentMethodKey, method);
	flushConfig();
}

int RenderConfig::getLoggingLevel(int lvl) const
{
	//return configTree_->get<int>(renderLoggingLevel, lvl);
	return {};
}

void RenderConfig::setLoggingLevel(int lvl)
{
	//configTree_->put(renderLoggingLevel, lvl);
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
	file << configTree_->dump(1, '\t');
}
