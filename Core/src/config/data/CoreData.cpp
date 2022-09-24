#include "./CoreData.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::core::config;

void CubA4::core::config::to_json(nlohmann::json& j, const CoreData& v)
{
	j = nlohmann::json
	{
		{"world", v.world},
		{"render", v.render},
		{"mods", v.mods}
	};
}

void CubA4::core::config::from_json(const nlohmann::json& j, CoreData& v)
{
	j.at("world").get_to(v.world);
	j.at("render").get_to(v.render);
	j.at("mods").get_to(v.mods);
}

