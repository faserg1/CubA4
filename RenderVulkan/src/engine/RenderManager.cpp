#include "./RenderManager.hpp"
#include "./ResourceManager.hpp"
#include "material/MaterialManager.hpp"
#include "model/ModelManager.hpp"
#include "world/WorldManager.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

RenderManager::RenderManager(std::shared_ptr<const Device> device,
	std::shared_ptr<const Render> render) :
	device_(device), render_(render)
{
	resourceManager_ = std::make_shared<ResourceManager>(device);
	materialManager_ = std::make_shared<material::MaterialManager>(device, render, resourceManager_);
	modelManager_ = std::make_shared<model::ModelManager>(device);
	worldManager_ = std::make_shared<world::WorldManager>(device, resourceManager_);
}

RenderManager::~RenderManager()
{
	
}

std::shared_ptr<material::IMaterialManager> RenderManager::getMaterialManager() const
{
	return materialManager_;
}

std::shared_ptr<model::IModelManager> RenderManager::getModelManager() const
{
	return modelManager_;
}

std::shared_ptr<world::IWorldManager> RenderManager::getWorldManager() const
{
	return worldManager_;
}