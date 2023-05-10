#include <config/data/RenderData.hpp>
#include <nlohmann/json.hpp>
using namespace CubA4::render::config;

namespace CubA4::render::config
{
	void from_json(const nlohmann::json& j, RenderData& v)
	{
		if (j.contains("presentation"))
			j.at("presentation").get_to(v.presentation);
		if (j.contains("misc"))
			j.at("misc").get_to(v.misc);
		if (j.contains("quality"))
			j.at("quality").get_to(v.quality);
	}

	void to_json(nlohmann::json& j, const RenderData& v)
	{
		j = nlohmann::json
		{
			{"presentation", v.presentation},
			{"misc", v.misc},
			{"quality", v.quality}
		};
	}
}