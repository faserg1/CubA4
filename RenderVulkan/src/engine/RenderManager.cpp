#include "./RenderManager.hpp"
#include "material/MaterialManager.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

RenderManager::RenderManager(std::shared_ptr<const Device> device) :
	device_(device)
{
	materialManager_ = std::make_shared<material::MaterialManager>(device);
}

RenderManager::~RenderManager()
{
	
}

std::shared_ptr<material::IMaterialManager> RenderManager::getMaterialManager() const
{
	return materialManager_;
}