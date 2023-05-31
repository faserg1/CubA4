#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>
#include <unordered_map>

namespace CubA4::config
{
	struct ModsData
	{
		std::string mainMod;
		std::unordered_map<std::string, std::string> overridedFeatures;
	};
	
	void from_json(const nlohmann::json& j, ModsData& v);
	void to_json(nlohmann::json& j, const ModsData& v);
}
