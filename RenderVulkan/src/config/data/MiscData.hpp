#pragma once

#include <nlohmann/json_fwd.hpp>

namespace CubA4::render::config
{
	struct MiscData
	{
		int logLevel = 0;
	};

	void from_json(const nlohmann::json& j, MiscData& v);
	void to_json(nlohmann::json& j, const MiscData& v);
}
