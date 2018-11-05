#include "ModManager.hpp"
#include "ModRenderManager.hpp"
using namespace CubA4::mod::manager;

ModManager::ModManager() :
	renderManager_(std::make_shared<ModRenderManager>())
{
	
}

ModManager::~ModManager()
{
	
}

std::weak_ptr<const IModRenderManager> ModManager::getModRenderManager() const
{
	return renderManager_;
}

std::shared_ptr<ModRenderManager> ModManager::getModRenderManager()
{
	return renderManager_;
}