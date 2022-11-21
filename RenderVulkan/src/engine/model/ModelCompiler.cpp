#include "./ModelCompiler.hpp"
#include <algorithm>
#include <execution>
using namespace CubA4::render::engine::model;

void ModelCompiler::addFaces(std::vector<CollectedData> data)
{
	collected_ = std::move(data);
}

std::shared_ptr<const RenderModel> ModelCompiler::compile(const std::string &id, std::shared_ptr<ModelManager> modelManager)
{
	size_t vertex_size = 0;
	size_t faces_size = 0;
	for (auto &data : collected_)
	{
		const auto model = data.model;
		const auto &faces = data.faces;
		const auto &indexes = model->getFaceIndices();
		data.faceOffset_ = faces_size;
		faces_size += faces.size();
		data.faceOffsets_ = std::move(calculateOffsets(indexes));
		data.vertexOffset_ = vertex_size;
		for (auto faceIdx : faces)
		{
			auto faceSize = indexes.faces[faceIdx];
			vertex_size += faceSize;
		}
	}
	data_.vertices.resize(vertex_size);
	data_.uvws.resize(vertex_size);
	data_.faces.indexes.resize(vertex_size);
	data_.faces.faces.resize(faces_size);
	
	std::for_each(std::execution::par_unseq, collected_.begin(), collected_.end(), [this](const auto &data)
	{
		const auto &model = data.model;
		const auto &faces = data.faces;
		const auto &pos = data.pos;
		const auto &offsets = data.faceOffsets_;
		const auto &vertices = model->getVertices();
		const auto &uvws = model->getUVWCoords();
		const auto &indexes = model->getFaceIndices();
		size_t newVertexIdx = data.vertexOffset_;
		size_t newFaceIdx = data.faceOffset_;
		for (auto faceIdx : faces)
		{
			auto faceOffset = offsets[faceIdx];
			auto faceSize = indexes.faces[faceIdx];
			data_.faces.faces[newFaceIdx++] = faceSize;
			for (size_t fIdx = faceOffset; fIdx < faceOffset + faceSize; fIdx++)
			{
				data_.faces.indexes[newVertexIdx] = static_cast<CubA4::model::FaceIndices::IndexType>(newVertexIdx);
				auto idx = indexes.indexes[fIdx];
				auto vertex = vertices[idx];
				auto uvw = uvws[idx];
				vertex.x += pos.x;
				vertex.y += pos.y;
				vertex.z += pos.z;
				data_.vertices[newVertexIdx] = vertex;
				data_.uvws[newVertexIdx] = uvw;
				newVertexIdx++;
			}
		}
	});
	
	data_.id = id;
	if (data_.vertices.empty() || data_.faces.indexes.empty())
		return {};
	return modelManager->createModel(data_);
}

std::vector<size_t> ModelCompiler::calculateOffsets(const CubA4::model::FaceIndices &indices)
{
	std::vector<size_t> offsets(indices.faces.size());
	size_t tempOffset = 0;
	for (size_t i = 0; i < offsets.size(); i++)
	{
		offsets[i] = tempOffset;
		tempOffset += indices.faces[i];
	}
	return std::move(offsets);
}