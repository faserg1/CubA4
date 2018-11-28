#include "ModRenderManager.hpp"
#include <engine/model/IRenderModel.hpp>
using namespace CubA4::mod::manager;

ModRenderManager::ModRenderManager()
{
	
}

ModRenderManager::~ModRenderManager()
{
	
}

std::shared_ptr<const CubA4::render::engine::model::IRenderModel> ModRenderManager::getModel(const std::string &id) const
{
	auto it = map_.find(id);
	if (it == map_.end())
		return {};
	return it->second;
}

void ModRenderManager::registerRenderModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel)
{
	if (map_.find(renderModel->getId()) != map_.end())
		return;
	map_.insert(std::make_pair(renderModel->getId(), renderModel));
}