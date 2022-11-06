#pragma once

#include <vector>
#include <cstdint>

namespace CubA4::model
{
	/// Вершина
	struct Vertex
	{
		float x;
		float y;
		float z;
	};

	struct UVWCoords
	{
		float u;
		float v;
		float w;
	};

	struct Face
	{
		std::vector<uint16_t> indexes;
	};
}