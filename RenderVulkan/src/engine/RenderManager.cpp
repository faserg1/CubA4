#include "./RenderManager.hpp"
#include "./ResourceManager.hpp"
#include "material/MaterialManager.hpp"
#include "model/ModelManager.hpp"
#include "world/WorldManager.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::model;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

RenderManager::RenderManager(std::shared_ptr<const Device> device,
	std::shared_ptr<const ICore> core,
	std::shared_ptr<const Render> render) :
	device_(device), core_(core), render_(render)
{
	resourceManager_ = std::make_shared<ResourceManager>(device, core_);
	materialManager_ = std::make_shared<MaterialManager>(device, render, resourceManager_);
	modelManager_ = std::make_shared<ModelManager>(device);
	worldManager_ = std::make_shared<WorldManager>(device, resourceManager_);
}

RenderManager::~RenderManager()
{
	
}

std::shared_ptr<IMaterialManager> RenderManager::getMaterialManager() const
{
	return materialManager_;
}

std::shared_ptr<IModelManager> RenderManager::getModelManager() const
{
	return modelManager_;
}

std::shared_ptr<ModelManager> RenderManager::getModelManager()
{
	return modelManager_;
}

std::shared_ptr<IWorldManager> RenderManager::getWorldManager() const
{
	return worldManager_;
}

std::shared_ptr<ResourceManager> RenderManager::getResourceManager() const
{
	return resourceManager_;
}