#pragma once

#include <nlohmann/json_fwd.hpp>
#include <model/RenderModelData.hpp>

namespace CubA4::model
{
	void from_json(const nlohmann::json& j, BlockRenderModelData& v);
	void to_json(nlohmann::json& j, const BlockRenderModelData& v);

	void from_json(const nlohmann::json& j, RenderModelData& v);
	void to_json(nlohmann::json& j, const RenderModelData& v);
}
