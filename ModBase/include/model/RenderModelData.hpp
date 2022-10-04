#pragma once

#include <world/Sides.hpp>
#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace CubA4
{
	namespace mod
	{
		namespace model
		{
			struct RenderModelData
			{
				struct VertexUVW
				{
					float x, y, z;
					float u, v, w;
				};
				struct Material
				{
					std::string materialId;
					std::vector<uint16_t> faces;
				};
				std::vector<VertexUVW> vertices;
				std::vector<Material> faces;

				std::map<world::BlockSide, std::vector<uint16_t>> hide;
				std::map<world::BlockSide, std::vector<uint16_t>> hidden;
			};
		}
	}
}
