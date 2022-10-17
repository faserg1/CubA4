#include "./SimpleRenderModelDefinition.hpp"
#include <algorithm>
#include <ranges>
using namespace CubA4::core::model;
using namespace CubA4::core::world;

SimpleRenderModelDefinition::SimpleRenderModelDefinition(const std::string &id, const model::RenderModelData &data) : id_(id)
{
	vertices_.resize(data.vertices.size());
	uvws_.resize(data.vertices.size());
	for (size_t i = 0; i < vertices_.size(); i++)
	{
		vertices_[i].x = data.vertices[i].x;
		vertices_[i].y = data.vertices[i].y;
		vertices_[i].z = data.vertices[i].z;
		uvws_[i].u = data.vertices[i].u;
		uvws_[i].v = data.vertices[i].v;
		uvws_[i].w = data.vertices[i].w;
	}
	faces_.reserve(data.faces.size());
	std::transform(data.faces.begin(), data.faces.end(), std::back_inserter(faces_), [](const RenderModelData::Face &face) -> Face
	{
		return Face
		{
			.indexes = face.indexes
		};
	});
	nonOpaque = data.nonOpaque;
}

SimpleRenderModelDefinition::~SimpleRenderModelDefinition()
{
	
}

const std::string &SimpleRenderModelDefinition::getId() const
{
	return id_;
}

std::vector<std::string> SimpleRenderModelDefinition::getUsedMaterials() const
{
	auto range = std::views::keys(materialToFaces_);
	return std::vector(range.begin(), range.end());
}

const std::vector<Face> &SimpleRenderModelDefinition::getFaceIndices() const
{
	return faces_;
}

const std::vector<Vertex> &SimpleRenderModelDefinition::getVertices() const
{
	return vertices_;
}

const std::vector<UVWCoords> &SimpleRenderModelDefinition::getUVWCoords() const
{
	return uvws_;
}

std::vector<unsigned short> SimpleRenderModelDefinition::getFaces(const std::string &materialId, std::vector<BlockSide> hiddenSides, const BlockData& data) const
{
	// assume, that if we have 6 sides and all them are hidden, we have nothing to render
	if (hiddenSides.size() == 6)
		return {};
	return {};
}

std::vector<BlockSide> SimpleRenderModelDefinition::getNonOpaqueSide(const std::string &materialId, const BlockData& data) const
{
	return nonOpaque;
}