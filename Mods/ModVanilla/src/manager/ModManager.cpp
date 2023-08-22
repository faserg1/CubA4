#include <manager/ModManager.hpp>
using namespace CubA4::manager;

ModManager::ModManager() :
	blockManager_(std::make_shared<ModBlockManager>()),
	entityManager_(std::make_shared<ModEntityManager>()),
	renderManager_(std::make_shared<ModRenderManager>())
{
	
}

ModManager::~ModManager()
{
	
}

std::shared_ptr<const IModBlockManager> ModManager::getBlockManager() const
{
	return blockManager_;
}

std::shared_ptr<ModBlockManager> ModManager::getBlockManager()
{
	return blockManager_;
}

std::shared_ptr<const IModEntityManager> ModManager::getEntityManager() const
{
	return entityManager_;
}

std::shared_ptr<ModEntityManager> ModManager::getEntityManager()
{
	return entityManager_;
}

std::shared_ptr<const IModRenderManager> ModManager::getRenderManager() const
{
	return renderManager_;
}

std::shared_ptr<ModRenderManager> ModManager::getRenderManager()
{
	return renderManager_;
}