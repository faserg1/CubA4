#include <config/data/QualityData.hpp>
#include <nlohmann/json.hpp>
using namespace CubA4::render::config;

namespace CubA4::render::config
{
	void from_json(const nlohmann::json& j, QualityData& v)
	{
		if (j.contains("antialiasing"))
			j.at("antialiasing").get_to(v.antialiasing);
		if (j.contains("chunk_distance"))
			j.at("chunk_distance").get_to(v.chunkDistance);
	}

	void to_json(nlohmann::json& j, const QualityData& v)
	{
		j = nlohmann::json
		{
			{"antialiasing", v.antialiasing},
			{"chunk_distance", v.chunkDistance},
		};
	}
}