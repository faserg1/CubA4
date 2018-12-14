#include "./WorldManager.hpp"
#include "../ResourceManager.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::world;
using namespace CubA4::render::vulkan;

WorldManager::WorldManager(std::shared_ptr<const Device> device, std::shared_ptr<ResourceManager> resourceManager) :
	device_(device), resourceManager_(resourceManager)
{
	pool_ = resourceManager_->getBuiltInPool();
	layout_ = resourceManager_->getBuiltInLayout();
	allocateSets();
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

sVkDescriptorSet WorldManager::getWorldDescriptorSetLayout() const
{
	return worldSet_;
}

void WorldManager::allocateSets()
{
	VkDescriptorSetLayout layouts[] = { layout_->get() };

	VkDescriptorSetAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	info.descriptorPool = pool_->get();
	info.descriptorSetCount = 1;
	info.pSetLayouts = layouts;

	VkDescriptorSet set = {};

	vkAllocateDescriptorSets(device_->getDevice(), &info, &set);

	std::function<void(VkDescriptorSet)> deleter = [dev = device_, p = pool_](VkDescriptorSet set)
	{
		vkFreeDescriptorSets(dev->getDevice(), p->get(), 1, &set);
	};

	worldSet_ = util::createSharedVulkanObject(set, deleter);
}