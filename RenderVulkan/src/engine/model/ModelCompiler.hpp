#pragma once

#include <memory>
#include <model/IRenderModelDefinition.hpp>
#include <world/Position.hpp>
#include "./RenderModel.hpp"
#include "./ModelManager.hpp"

namespace CubA4::render::engine::model
{
	class ModelCompiler
	{
		using Model = std::shared_ptr<const CubA4::model::IRenderModelDefinition>;
		using Faces = std::vector<unsigned short>;
	public:
		ModelCompiler() = default;

		void addFaces(Model model, Faces faces, CubA4::world::BlockInChunkPos pos);
		[[nodiscard]] std::shared_ptr<const RenderModel> compile(const std::string &id, std::shared_ptr<ModelManager> modelManager);
	private:
		std::vector<size_t> calculateOffsets(const CubA4::model::FaceIndices &indices);
	private:
		struct : public CubA4::model::IRenderModelDefinition
		{
			std::string id;
			std::vector<CubA4::model::Vertex> vertices;
			std::vector<CubA4::model::UVWCoords> uvws;
			CubA4::model::FaceIndices faces;

			const std::string &getId() const { return id; }
			std::vector<std::string> getUsedMaterials() const override { return {}; }
			const CubA4::model::FaceIndices &getFaceIndices() const override { return faces; }
			const std::vector<CubA4::model::Vertex> &getVertices() const override { return vertices; }
			const std::vector<CubA4::model::UVWCoords> &getUVWCoords() const override { return uvws; }
			RMaterial getMaterial(const std::string &materialId) const override { return {}; }
		} data_;
		struct TempData
		{
			Model model;
			Faces faces;
			CubA4::world::BlockInChunkPos pos;
		};
		std::vector<TempData> collected_;
	};
}