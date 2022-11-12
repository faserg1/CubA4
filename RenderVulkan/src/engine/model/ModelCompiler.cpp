#include "./ModelCompiler.hpp"
using namespace CubA4::render::engine::model;

void ModelCompiler::addFaces(Model model, Faces faces, CubA4::world::BlockInChunkPos pos)
{
	collected_.push_back({model, std::move(faces), pos});
}

std::shared_ptr<const RenderModel> ModelCompiler::compile(const std::string &id, std::shared_ptr<ModelManager> modelManager)
{
	size_t vertex_size = 0;
	size_t faces_size = 0;
	for (const auto &data : collected_)
	{
		const auto model = data.model;
		const auto &faces = data.faces;
		const auto &indexes = model->getFaceIndices();
		faces_size += faces.size();
		for (auto faceIdx : faces)
		{
			auto &face = indexes[faceIdx];
			vertex_size += face.indexes.size();
		}
	}
	data_.vertices.resize(vertex_size);
	data_.uvws.resize(vertex_size);
	data_.faces.resize(faces_size);
	size_t newFaceIdx = 0;
	size_t newVertexIdx = 0;
	for (const auto &data : collected_)
	{
		const auto model = data.model;
		const auto &faces = data.faces;
		const auto pos = data.pos;
		const auto &vertices = model->getVertices();
		const auto &uvws = model->getUVWCoords();
		const auto &indexes = model->getFaceIndices();
		for (auto faceIdx : faces)
		{
			const auto &face = indexes[faceIdx];
			auto &newFace = data_.faces[newFaceIdx++];
			newFace.indexes.resize(face.indexes.size());
			size_t newIndexIdx = 0;
			for (auto idx : face.indexes)
			{
				newFace.indexes[newIndexIdx] = static_cast<CubA4::model::Face::IndexType>(newVertexIdx);
				auto vertex = vertices[idx];
				auto uvw = uvws[idx];
				vertex.x += pos.x;
				vertex.y += pos.y;
				vertex.z += pos.z;
				data_.vertices[newVertexIdx] = vertex;
				data_.uvws[newVertexIdx] = uvw;
				newVertexIdx++;
				newIndexIdx++;
			}
		}
	}
	
	data_.id = id;
	if (data_.vertices.empty() || data_.faces.empty())
		return {};
	return modelManager->createModel(data_);
}