#include "./RenderModelDataJson.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::mod::model;

namespace CubA4::mod::model
{
	void to_json(nlohmann::json& j, const RenderModelData::VertexUVW& v);
	void from_json(const nlohmann::json& j, RenderModelData::VertexUVW& v);
	void to_json(nlohmann::json& j, const RenderModelData::Material& v);
	void from_json(const nlohmann::json& j, RenderModelData::Material& v);
}

void CubA4::mod::model::to_json(nlohmann::json& j, const RenderModelData::VertexUVW& v)
{
	j = nlohmann::json
	{
		{"x", v.x},
		{"y", v.y},
		{"z", v.z},
		{"u", v.u},
		{"v", v.v},
		{"w", v.w},
	};
}

void CubA4::mod::model::from_json(const nlohmann::json& j, RenderModelData::VertexUVW& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
	j.at("z").get_to(v.z);
	j.at("u").get_to(v.u);
	j.at("v").get_to(v.v);
	j.at("w").get_to(v.w);
}

void CubA4::mod::model::to_json(nlohmann::json& j, const RenderModelData::Material& v)
{
	j = nlohmann::json
	{
		{"id", v.materialId},
		{"faces", v.faces}
	};
}

void CubA4::mod::model::from_json(const nlohmann::json& j, RenderModelData::Material& v)
{
	j.at("id").get_to(v.materialId);
	j.at("faces").get_to(v.faces);
}


void CubA4::mod::model::to_json(nlohmann::json& j, const RenderModelData& v)
{
	j = nlohmann::json
	{
		{"vertices", v.vertices},
		{"faces", v.faces},
		{"hide", v.hide},
		{"hidden", v.hidden},
	};
}

void CubA4::mod::model::from_json(const nlohmann::json& j, RenderModelData& v)
{
	j.at("vertices").get_to(v.vertices);
	j.at("faces").get_to(v.faces);
	j.at("hide").get_to(v.hide);
	j.at("hidden").get_to(v.hidden);
}


