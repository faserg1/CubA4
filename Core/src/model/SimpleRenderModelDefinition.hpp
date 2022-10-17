#pragma once

#include <model/IRenderModelDefinition.hpp>
#include <model/RenderModelData.hpp>
#include <unordered_map>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class SimpleRenderModelDefinition : public virtual mod::model::IRenderModelDefinition
			{
			public:
				explicit SimpleRenderModelDefinition(const std::string &id, const model::RenderModelData &data);
				~SimpleRenderModelDefinition();

				const std::string &getId() const override;
				std::vector<std::string> getUsedMaterials() const override;
				const std::vector<core::model::Face> &getFaceIndices() const override;
				const std::vector<core::model::Vertex> &getVertices() const override;
				const std::vector<core::model::UVWCoords> &getUVWCoords() const override;
				std::vector<unsigned short> getFaces(const std::string &materialId, std::vector<core::world::BlockSide> hiddenSides, const core::world::BlockData& data) const override;
				std::vector<core::world::BlockSide> getNonOpaqueSide(const std::string &materialId, const core::world::BlockData& data) const override;
			private:
				const std::string id_;
				std::vector<Face> faces_;
				std::unordered_map<std::string, std::vector<uint16_t>> materialToFaces_;
				std::vector<core::model::Vertex> vertices_;
				std::vector<core::model::UVWCoords> uvws_;
				std::vector<core::world::BlockSide> nonOpaque;
			};
		}
	}
}
