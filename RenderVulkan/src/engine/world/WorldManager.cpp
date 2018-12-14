#include "./WorldManager.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

WorldManager::WorldManager(std::shared_ptr<const Device> device, std::shared_ptr<ResourceManager> resourceManager) :
	device_(device), resourceManager_(resourceManager)
{
	
}

WorldManager::~WorldManager()
{
	
}

void WorldManager::setCameraPosition(double x, double y, double z)
{

}

void WorldManager::setCameraRotation(double roll, double pitch, double yaw)
{

}

void WorldManager::setFieldOfView(float degrees)
{

}