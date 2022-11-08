#include <config/data/MiscData.hpp>
#include <nlohmann/json.hpp>
using namespace CubA4::render::config;

namespace CubA4::render::config
{
	void from_json(const nlohmann::json& j, MiscData& v)
	{
		j.at("log_level").get_to(v.logLevel);
	}

	void to_json(nlohmann::json& j, const MiscData& v)
	{
		j = nlohmann::json
		{
			{"log_level", v.logLevel}
		};
	}
}