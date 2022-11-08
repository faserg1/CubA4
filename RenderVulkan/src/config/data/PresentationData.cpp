#include <config/data/PresentationData.hpp>
#include <nlohmann/json.hpp>
using namespace CubA4::render::config;

namespace CubA4::render::config
{
	void from_json(const nlohmann::json& j, PresentationData& v)
	{
		j.at("width").get_to(v.width);
		j.at("height").get_to(v.height);
		j.at("method").get_to(v.method);
	}

	void to_json(nlohmann::json& j, const PresentationData& v)
	{
		j = nlohmann::json
		{
			{"width", v.width},
			{"height", v.height},
			{"method", v.method}
		};
	}
}