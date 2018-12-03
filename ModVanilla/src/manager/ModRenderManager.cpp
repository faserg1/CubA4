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
	auto it = modelMap_.find(id);
	if (it == modelMap_.end())
		return {};
	return it->second;
}

std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout> ModRenderManager::getMaterialLayout(const std::string &id) const
{
	auto it = materialLayoutMap_.find(id);
	if (it == materialLayoutMap_.end())
		return {};
	return it->second;
}

std::shared_ptr<const CubA4::render::engine::material::IMaterial> ModRenderManager::getMaterial(const std::string &id) const
{
	auto it = materialMap_.find(id);
	if (it == materialMap_.end())
		return {};
	return it->second;
}

void ModRenderManager::registerRenderModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel)
{
	if (modelMap_.find(renderModel->getId()) != modelMap_.end())
		return;
	modelMap_.insert(std::make_pair(renderModel->getId(), renderModel));
}

void ModRenderManager::registerMaterialLayout(std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout> renderMaterialLayout, const std::string &id)
{
	if (materialLayoutMap_.find(id) != materialLayoutMap_.end())
		return;
	materialLayoutMap_.insert(std::make_pair(id, renderMaterialLayout));
}

void ModRenderManager::registerMaterial(std::shared_ptr<const CubA4::render::engine::material::IMaterial> renderMaterial, const std::string &id)
{
	if (materialMap_.find(id) != materialMap_.end())
		return;
	materialMap_.insert(std::make_pair(id, renderMaterial));
}