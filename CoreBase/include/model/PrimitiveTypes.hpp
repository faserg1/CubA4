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

	struct FaceIndices
	{
		using IndexType = uint16_t;
		/// @brief all the vertex indexes, 
		std::vector<IndexType> indexes;
		/// @brief for each face the length of the indecies to consume
		std::vector<size_t> faces;
	};
}