#include "./RenderManager.hpp"
#include "./ResourceManager.hpp"
#include "material/MaterialManager.hpp"
#include "model/ModelManager.hpp"
#include "world/WorldManager.hpp"
#include <config/VulkanConfigAdapter.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::model;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

RenderManager::RenderManager(std::shared_ptr<const vulkan::Instance> instance,
	std::shared_ptr<const Device> device,
	std::shared_ptr<const ICore> core,
	std::shared_ptr<const RenderPassManager> rpManager,
	std::shared_ptr<const config::IRenderConfig> config) :
	instance_(instance), device_(device), core_(core), rpManager_(rpManager), config_(config)
{
	resourceManager_ = std::make_shared<ResourceManager>(device, core_);
	materialManager_ = std::make_shared<MaterialManager>(device, rpManager, resourceManager_, config_);
	modelManager_ = std::make_shared<ModelManager>(device);
	worldManager_ = std::make_shared<WorldManager>(device, resourceManager_);
	uiManager_ = std::make_shared<CubA4::render::ui::UIManager>(instance, device);
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

std::shared_ptr<world::WorldManager> RenderManager::getWorldManager()
{
	return worldManager_;
}

std::shared_ptr<ResourceManager> RenderManager::getResourceManager() const
{
	return resourceManager_;
}

std::shared_ptr<CubA4::render::ui::IRenderUIManager> RenderManager::getUIManager() const
{
	return uiManager_;
}

std::shared_ptr<CubA4::render::ui::UIManager> RenderManager::getUIManager()
{
	return uiManager_;
}