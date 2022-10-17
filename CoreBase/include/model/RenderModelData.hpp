#pragma once

#include <world/Sides.hpp>
#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace CubA4
{
	namespace core
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
				struct Face
				{
					std::vector<uint16_t> indexes;
				};
				std::vector<VertexUVW> vertices;
				std::vector<Face> faces;
				std::map<std::string, std::vector<uint16_t>> materials;

				std::vector<core::world::BlockSide> nonOpaque;
				std::map<core::world::BlockSide, std::vector<uint16_t>> hidden;
			};
		}
	}
}
