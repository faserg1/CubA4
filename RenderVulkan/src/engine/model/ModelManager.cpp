#include "./ModelManager.hpp"
#include <model/IRenderModelDefinition.hpp>
using namespace CubA4::render::engine::model;

ModelManager::ModelManager()
{
	
}

ModelManager::~ModelManager()
{
	
}

void ModelManager::registerModel(const CubA4::core::model::IRenderModelDefinition &renderModel)
{
	auto &vertices = renderModel.getVertices();
	auto &faces = renderModel.getFaceIndices();
}