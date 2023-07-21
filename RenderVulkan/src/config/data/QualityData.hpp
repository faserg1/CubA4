#pragma once

#include <nlohmann/json_fwd.hpp>

namespace CubA4::render::config
{
	struct QualityData
	{
		int antialiasing = 0;
		uint16_t chunkDistance = 16;
	};

	void from_json(const nlohmann::json& j, QualityData& v);
	void to_json(nlohmann::json& j, const QualityData& v);
}
