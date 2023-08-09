#include <model/SimpleRenderModelDefinition.hpp>
#include <algorithm>
#include <ranges>
#include <set>
#include <range/v3/range/conversion.hpp>
using namespace CubA4::model;
using namespace CubA4::world;

SimpleRenderModelDefinition::SimpleRenderModelDefinition(const std::string &id, const model::RenderModelData &data, RMaterialsMap materialsMap) :
	id_(id), materialsMap_(materialsMap)
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
	faces_.faces.resize(data.faces.size());
	size_t indexCount = 0;
	for (auto &face : data.faces)
	{
		indexCount += face.indexes.size();
	}
	faces_.indexes.resize(indexCount);
	size_t indexOffset = 0;
	size_t faceOffset = 0;
	for (auto &face : data.faces)
	{
		std::copy(face.indexes.begin(), face.indexes.end(), faces_.indexes.begin() + indexOffset);
		faces_.faces[faceOffset++] = face.indexes.size();
		indexOffset += face.indexes.size();
	}

	materialToFaces_ = data.materials | ranges::to<std::unordered_map>;
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

const FaceIndices &SimpleRenderModelDefinition::getFaceIndices() const
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

SimpleRenderModelDefinition::RMaterial SimpleRenderModelDefinition::getMaterial(const std::string &materialId) const
{
	if (auto result = materialsMap_.find(materialId); result != materialsMap_.end())
		return result->second;
	return {};
}
