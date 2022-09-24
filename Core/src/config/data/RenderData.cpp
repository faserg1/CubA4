#include "./RenderData.hpp"
#include <nlohmann/json.hpp>
using namespace CubA4::core::config;

void CubA4::core::config::to_json(nlohmann::json& j, const RenderData& v)
{
	j = nlohmann::json
	{
		{"engine", v.engine}
	};
}

void CubA4::core::config::from_json(const nlohmann::json& j, RenderData& v)
{
	v.engine = j.value("engine", "vulkan");
}


