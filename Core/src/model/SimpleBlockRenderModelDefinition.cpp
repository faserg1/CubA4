#include <model/SimpleBlockRenderModelDefinition.hpp>
#include <algorithm>
#include <ranges>
#include <set>
#include <range/v3/range/conversion.hpp>
using namespace CubA4::model;
using namespace CubA4::world;

SimpleBlockRenderModelDefinition::SimpleBlockRenderModelDefinition(const std::string &id, const model::BlockRenderModelData &data, RMaterialsMap materialsMap) :
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

	nonOpaque_ = data.nonOpaque;
	hiddenFaces_ = data.hidden | ranges::to<std::unordered_map>;
	materialToFaces_ = data.materials | ranges::to<std::unordered_map>;
}

SimpleBlockRenderModelDefinition::~SimpleBlockRenderModelDefinition()
{
	
}

const std::string &SimpleBlockRenderModelDefinition::getId() const
{
	return id_;
}

std::vector<std::string> SimpleBlockRenderModelDefinition::getUsedMaterials() const
{
	auto range = std::views::keys(materialToFaces_);
	return std::vector(range.begin(), range.end());
}

const FaceIndices &SimpleBlockRenderModelDefinition::getFaceIndices() const
{
	return faces_;
}

const std::vector<Vertex> &SimpleBlockRenderModelDefinition::getVertices() const
{
	return vertices_;
}

const std::vector<UVWCoords> &SimpleBlockRenderModelDefinition::getUVWCoords() const
{
	return uvws_;
}

SimpleBlockRenderModelDefinition::RMaterial SimpleBlockRenderModelDefinition::getMaterial(const std::string &materialId) const
{
	if (auto result = materialsMap_.find(materialId); result != materialsMap_.end())
		return result->second;
	return {};
}

std::vector<unsigned short> SimpleBlockRenderModelDefinition::getFaces(const std::string &materialId, BlockSides hiddenSides, const BlockData& data) const
{
	constexpr const auto allSides = BlockSide::Back | BlockSide::Front | BlockSide::Left | BlockSide::Right | BlockSide::Top | BlockSide::Bottom;
	// assume, that if we have 6 sides and all them are hidden, we have nothing to render
	if (hiddenSides == allSides)
		return {};
	auto allFacesIt = materialToFaces_.find(materialId);
	if (allFacesIt == materialToFaces_.end())
		return {};
	std::vector<unsigned short> totalFaces;
	totalFaces.reserve(allFacesIt->second.size());
	std::set<unsigned short> hidden;
	for (const auto &pair : hiddenFaces_)
	{
		if (hiddenSides & pair.first)
		{
			for (auto idx : pair.second)
				hidden.insert(idx);
		}
	}
	for (auto idx : allFacesIt->second)
	{
		if (hidden.find(idx) == hidden.end())
			totalFaces.push_back(idx);
	}
	return std::move(totalFaces);
}

BlockSides SimpleBlockRenderModelDefinition::getNonOpaqueSide(const BlockData& data) const
{
	return nonOpaque_;
}