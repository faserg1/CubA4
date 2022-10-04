#include "./ModelReader.hpp"
#include "./RenderModelDataJson.hpp"
#include <filesystem>
#include <resources/IResource.hpp>
#include <nlohmann/json.hpp>
using namespace CubA4::core::model;

ModelReader::ModelReader()
{
	
}

ModelReader::~ModelReader()
{
	
}

CubA4::mod::model::RenderModelData ModelReader::readRenderModel(std::shared_ptr<resources::IResource> resource)
{
	std::string str;
	const auto size = resource->size();
	str.resize(size);
	resource->copyIn(str.data(), size, 0);
	auto json = nlohmann::json::parse(str);
	return json.get<CubA4::mod::model::RenderModelData>();
}