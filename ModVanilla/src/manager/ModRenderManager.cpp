#include <manager/ModRenderManager.hpp>
using namespace CubA4::manager;

ModRenderManager::ModRenderManager() = default;

void ModRenderManager::addModel(const std::string &id, std::shared_ptr<const ModelType> model)
{
	models_.insert(std::make_pair(id, model));
}

std::shared_ptr<const ModRenderManager::ModelType> ModRenderManager::getModel(const std::string &id) const
{
	if (auto it = models_.find(id); it != models_.end())
		return it->second;
	return {};
}