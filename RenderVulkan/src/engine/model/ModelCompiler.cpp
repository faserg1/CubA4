#include "./ModelCompiler.hpp"
#include <algorithm>
#include <execution>
#include <atomic>
#include <ctime>
#include <unordered_map>
using namespace CubA4::render::engine::model;

void ModelCompiler::addFaces(std::vector<CollectedData> data)
{
	auto it = std::remove_if(std::execution::par_unseq, data.begin(), data.end(), [](const CollectedData& data) -> bool
	{
		return !data.model || data.faces.empty();
	});
	if (it != data.end())
		data.erase(it, data.end());
	collected_ = std::move(data);
}

std::shared_ptr<const RenderModel> ModelCompiler::compile(const std::string &id, std::shared_ptr<ModelManager> modelManager)
{
	size_t vertex_size = 0;
	size_t faces_size = 0;

	std::clock_t start = std::clock();

	std::clock_t init = 0;
	std::clock_t offsets = 0;
	std::clock_t vSize = 0;

	std::unordered_map<const CubA4::model::FaceIndices*, std::vector<size_t>> offsetsMap;

	for (auto &data : collected_)
	{
		std::clock_t m1 = std::clock();
		const auto model = data.model;
		const auto &faces = data.faces;
		const auto &indexes = model->getFaceIndices();
		data.faceOffset_ = faces_size;
		faces_size += faces.size();
		data.vertexOffset_ = vertex_size;
		std::clock_t m2 = std::clock();
		if (auto it = offsetsMap.find(&indexes); it != offsetsMap.end())
		{
			data.faceOffsets_ = &it->second;
		}
		else
		{
			data.faceOffsets_ = &offsetsMap.insert(std::make_pair(&indexes, calculateOffsets(indexes))).first->second;
		}
		std::clock_t m3 = std::clock();
		std::atomic<size_t> currentVertexSize(0);
		std::for_each(std::execution::par_unseq, faces.begin(), faces.end(), [&indexes, &currentVertexSize](const auto faceIdx)
		{
			currentVertexSize += indexes.faces[faceIdx];
		});
		vertex_size += currentVertexSize.load();
		std::clock_t m4 = std::clock();
		init += m2 - m1;
		offsets += m3 - m2;
		vSize += m4 - m3;
		/*for (auto faceIdx : faces)
		{
			auto faceSize = indexes.faces[faceIdx];
			vertex_size += faceSize;
		}*/
	}

	std::clock_t mid1 = std::clock();

	data_.vertices.resize(vertex_size);
	data_.uvws.resize(vertex_size);
	data_.faces.indexes.resize(vertex_size);
	data_.faces.faces.resize(faces_size);

	std::clock_t mid2 = std::clock();
	
	std::for_each(std::execution::par_unseq, collected_.begin(), collected_.end(), [this](const auto &data)
	{
		const auto &model = data.model;
		const auto &faces = data.faces;
		const auto &pos = data.pos;
		const auto &offsets = *data.faceOffsets_;
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

	std::clock_t done = std::clock();

	auto total = done - start;
	auto prepare = mid1 - start;
	auto allocate = mid2 - mid1;
	auto compile = done - mid2;
	
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