#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

namespace CubA4::config
{
	struct ModsData
	{
		std::string mainMod;
	};
	
	void from_json(const nlohmann::json& j, ModsData& v);
	void to_json(nlohmann::json& j, const ModsData& v);
}
