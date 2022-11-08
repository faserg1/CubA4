#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace CubA4::render::config
{
	struct PresentationData
	{
		uint32_t width;
		uint32_t height;
		std::string method;
	};

	void from_json(const nlohmann::json& j, PresentationData& v);
	void to_json(nlohmann::json& j, const PresentationData& v);
}
