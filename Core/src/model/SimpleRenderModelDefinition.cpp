#include "./SimpleRenderModelDefinition.hpp"
#include <algorithm>
#include <ranges>
#include <range/v3/range/conversion.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/view/set_algorithm.hpp>
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
	faces_.reserve(data.faces.size());
	std::transform(data.faces.begin(), data.faces.end(), std::back_inserter(faces_), [](const RenderModelData::Face &face) -> Face
	{
		return Face
		{
			.indexes = face.indexes
		};
	});
	nonOpaque_ = data.nonOpaque;
	hiddenFaces_ = data.hidden | ranges::to<std::unordered_map>;
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

SimpleRenderModelDefinition::RMaterial SimpleRenderModelDefinition::getMaterial(const std::string &materialId) const
{
	if (auto result = materialsMap_.find(materialId); result != materialsMap_.end())
		return result->second;
	return {};
}

std::vector<unsigned short> SimpleRenderModelDefinition::getFaces(const std::string &materialId, BlockSides hiddenSides, const BlockData& data) const
{
	constexpr const auto allSides = BlockSide::Back | BlockSide::Front | BlockSide::Left | BlockSide::Right | BlockSide::Top | BlockSide::Bottom;
	// assume, that if we have 6 sides and all them are hidden, we have nothing to render
	if (hiddenSides == allSides)
		return {};
	auto allFacesIt = materialToFaces_.find(materialId);
	if (allFacesIt == materialToFaces_.end())
		return {};
	auto totalFaces = allFacesIt->second;
	// move to init?
	ranges::sort(totalFaces);
	for (const auto &pair : hiddenFaces_)
	{
		if (hiddenSides & pair.first)
		{
			totalFaces = ranges::views::set_difference(totalFaces, pair.second) | ranges::to<std::vector>;
		}
	}
	return totalFaces;
}

BlockSides SimpleRenderModelDefinition::getNonOpaqueSide(const BlockData& data) const
{
	return nonOpaque_;
}