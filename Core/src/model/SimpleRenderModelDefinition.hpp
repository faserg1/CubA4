#pragma once

#include <model/IBlockRenderModelDefinition.hpp>
#include <model/RenderModelData.hpp>
#include <unordered_map>

namespace CubA4::model
{
	class SimpleRenderModelDefinition : public virtual IBlockRenderModelDefinition
	{
	public:
		using RMaterialsMap = std::unordered_map<std::string, RMaterial>;
		explicit SimpleRenderModelDefinition(const std::string &id, const RenderModelData &data, RMaterialsMap materialsMap);
		~SimpleRenderModelDefinition();

		const std::string &getId() const override;
		std::vector<std::string> getUsedMaterials() const override;
		const FaceIndices &getFaceIndices() const override;
		const std::vector<Vertex> &getVertices() const override;
		const std::vector<UVWCoords> &getUVWCoords() const override;
		RMaterial getMaterial(const std::string &materialId) const override;
		std::vector<unsigned short> getFaces(const std::string &materialId, world::BlockSides hiddenSides, const world::BlockData& data) const override;
		world::BlockSides getNonOpaqueSide(const world::BlockData& data) const override;
	private:
		const std::string id_;
		FaceIndices faces_;
		std::unordered_map<std::string, std::vector<uint16_t>> materialToFaces_;
		std::vector<Vertex> vertices_;
		std::vector<UVWCoords> uvws_;
		world::BlockSides nonOpaque_;
		std::unordered_map<world::BlockSide, std::vector<uint16_t>> hiddenFaces_;
		RMaterialsMap materialsMap_;
	};
}
