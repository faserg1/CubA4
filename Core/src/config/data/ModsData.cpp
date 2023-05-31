#include "./ModsData.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::config;

void CubA4::config::to_json(nlohmann::json& j, const ModsData& v)
{
	j = nlohmann::json
	{
		{"main_mod", v.mainMod},
		{"overrided_features", v.overridedFeatures}
	};
}

void CubA4::config::from_json(const nlohmann::json& j, ModsData& v)
{
	v.mainMod = j.value("main_mod", "vanilla");
	v.overridedFeatures = j.value("overrided_features", decltype(v.overridedFeatures){});
}


