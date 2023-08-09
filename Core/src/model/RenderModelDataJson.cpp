#include "./RenderModelDataJson.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::model;

namespace CubA4::model
{
	void to_json(nlohmann::json& j, const RenderModelData::VertexUVW& v);
	void from_json(const nlohmann::json& j, RenderModelData::VertexUVW& v);
	void to_json(nlohmann::json& j, const RenderModelData::Face& v);
	void from_json(const nlohmann::json& j, RenderModelData::Face& v);
}

void CubA4::model::to_json(nlohmann::json& j, const RenderModelData::VertexUVW& v)
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

void CubA4::model::from_json(const nlohmann::json& j, RenderModelData::VertexUVW& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
	j.at("z").get_to(v.z);
	j.at("u").get_to(v.u);
	j.at("v").get_to(v.v);
	j.at("w").get_to(v.w);
}

void CubA4::model::to_json(nlohmann::json& j, const RenderModelData::Face& v)
{
	j = nlohmann::json
	{
		{"indexes", v.indexes}
	};
}

void CubA4::model::from_json(const nlohmann::json& j, RenderModelData::Face& v)
{
	j.at("indexes").get_to(v.indexes);
}

void CubA4::model::to_json(nlohmann::json& j, const RenderModelData& v)
{
	j = nlohmann::json
	{
		{"vertices", v.vertices},
		{"faces", v.faces},
		{"materials", v.materials}
	};
}

void CubA4::model::from_json(const nlohmann::json& j, RenderModelData& v)
{
	j.at("vertices").get_to(v.vertices);
	j.at("faces").get_to(v.faces);
	j.at("materials").get_to(v.materials);
}

void CubA4::model::to_json(nlohmann::json& j, const BlockRenderModelData& v)
{
	j = nlohmann::json
	{
		{"vertices", v.vertices},
		{"faces", v.faces},
		{"materials", v.materials},
		{"non_opaque", v.nonOpaque},
		{"hidden", v.hidden},
	};
}

void CubA4::model::from_json(const nlohmann::json& j, BlockRenderModelData& v)
{
	j.at("vertices").get_to(v.vertices);
	j.at("faces").get_to(v.faces);
	j.at("materials").get_to(v.materials);
	j.at("non_opaque").get_to(v.nonOpaque);
	j.at("hidden").get_to(v.hidden);
}


