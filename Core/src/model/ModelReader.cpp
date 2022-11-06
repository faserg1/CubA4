#include "./ModelReader.hpp"
#include "./RenderModelDataJson.hpp"
#include <filesystem>
#include <resources/IResource.hpp>
#include <nlohmann/json.hpp>
using namespace CubA4::model;

ModelReader::ModelReader()
{
	
}

ModelReader::~ModelReader()
{
	
}

RenderModelData ModelReader::readRenderModel(std::shared_ptr<const resources::IResource> resource) const
{
	std::string str;
	const auto size = resource->size();
	str.resize(size);
	resource->copyIn(str.data(), size, 0);
	auto json = nlohmann::json::parse(str);
	return json.get<RenderModelData>();
}

void ModelReader::writeRenderModel(std::shared_ptr<resources::IResource> resource, const RenderModelData &model)
{
	nlohmann::json j = model;
	const auto data = j.dump();
	resource->save(data.data(), data.size());
}