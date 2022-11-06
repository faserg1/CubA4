#pragma once

#include <nlohmann/json_fwd.hpp>
#include <memory>
#include "./ModsData.hpp"
#include "./RenderData.hpp"
#include "./WorldData.hpp"

namespace CubA4::config
{
	struct CoreData
	{
		WorldData world;
		ModsData mods;
		RenderData render;
	};
	
	void from_json(const nlohmann::json& j, CoreData& v);
	void to_json(nlohmann::json& j, const CoreData& v);
}
