#pragma once

#include <nlohmann/json_fwd.hpp>
#include <cstdint>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			struct WorldData
			{
				unsigned short chunkSize;	
			};
			
			void from_json(const nlohmann::json& j, WorldData& v);
			void to_json(nlohmann::json& j, const WorldData& v);
		}
	}
}
