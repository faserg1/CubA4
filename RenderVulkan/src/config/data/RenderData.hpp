#pragma once

#include <nlohmann/json_fwd.hpp>
#include <config/data/PresentationData.hpp>
#include <config/data/MiscData.hpp>
#include <config/data/QualityData.hpp>

namespace CubA4::render::config
{
	struct RenderData
	{
		PresentationData presentation;
		MiscData misc;
		QualityData quality;
	};

	void from_json(const nlohmann::json& j, RenderData& v);
	void to_json(nlohmann::json& j, const RenderData& v);
}
