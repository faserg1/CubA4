#include "./WorldData.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::config;

void CubA4::config::to_json(nlohmann::json& j, const WorldData& v)
{
	j = nlohmann::json
	{
		
	};
}

void CubA4::config::from_json(const nlohmann::json& j, WorldData& v)
{
	
}


