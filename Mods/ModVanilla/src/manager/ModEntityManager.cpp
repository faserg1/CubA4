#include <manager/ModEntityManager.hpp>
using namespace CubA4::manager;

ModEntityManager::ModEntityManager()
{
	
}

ModEntityManager::~ModEntityManager()
{
	
}

void ModEntityManager::addEntityFactory(const std::string &id, std::shared_ptr<const CubA4::object::IEntityFactory> factory)
{
	entityFactories_.insert(std::make_pair(id, factory));
}

std::shared_ptr<const CubA4::object::IEntityFactory> ModEntityManager::getEntityFactory(const std::string &id) const
{
	if (auto it = entityFactories_.find(id); it != entityFactories_.end())
		return it->second;
	return {};
}