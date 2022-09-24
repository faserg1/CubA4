#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			struct RenderData
			{
				std::string engine;
			};
			
			void from_json(const nlohmann::json& j, RenderData& v);
			void to_json(nlohmann::json& j, const RenderData& v);
		}
	}
}
