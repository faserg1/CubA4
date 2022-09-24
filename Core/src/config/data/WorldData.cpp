#include "./WorldData.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::core::config;

void CubA4::core::config::to_json(nlohmann::json& j, const WorldData& v)
{
	j = nlohmann::json
	{
		{"chunk_size", v.chunkSize}
	};
}

void CubA4::core::config::from_json(const nlohmann::json& j, WorldData& v)
{
	v.chunkSize = j.value("chunk_size", 16);
}


