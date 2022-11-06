#include "./ModelCompiler.hpp"
using namespace CubA4::render::engine::model;

void ModelCompiler::addFaces(Model model, Faces faces, CubA4::world::BlockInChunkPos pos)
{
	const auto vertices = model->getVertices();
	const auto uvws = model->getUVWCoords();
	const auto indexes = model->getFaceIndices();
	size_t total_size = 0;
	for (auto faceIdx : faces)
	{
		auto face = indexes[faceIdx];
		total_size += face.indexes.size();
	}
	data_.vertices.reserve(data_.vertices.size() + total_size);
	data_.uvws.reserve(data_.uvws.size() + total_size);
	for (auto faceIdx : faces)
	{
		auto face = indexes[faceIdx];
		decltype(face) newFace;
		newFace.indexes.resize(face.indexes.size());
		size_t newVertexIdx = 0;
		for (auto idx : face.indexes)
		{
			newFace.indexes[newVertexIdx++] = data_.vertices.size();
			auto vertex = vertices[idx];
			auto uvw = vertices[idx];
			vertex.x += pos.x;
			vertex.y += pos.y;
			vertex.z += pos.z;
			data_.vertices.push_back(vertex);
			data_.vertices.push_back(uvw);
		}
		data_.faces.push_back(newFace);
	}
}

std::shared_ptr<const RenderModel> ModelCompiler::compile(const std::string &id, std::shared_ptr<ModelManager> modelManager)
{
	data_.id = id;
	return modelManager->createModel(data_);
}