#include "./ResourceManager.hpp"
#include "../vulkan/Device.hpp"
#include "../VulkanInfoConst.hpp"
#include <vector>
#include <ICore.hpp>
#include <resources/IResourcesManager.hpp>
#include <engine/memory/QueuedOperations.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::util;

ResourceManager::ResourceManager(std::shared_ptr<const Device> device, std::shared_ptr<const ICore> core) :
	device_(device), core_(core), queuedOperations_(std::make_unique<QueuedOperations>(device))
{
	createBuildInDescriptorSetLayouts();
	createBuiltInDescriptorPool();
}

ResourceManager::~ResourceManager()
{

}

sVkDescriptorSetLayout ResourceManager::getWorldLayout() const
{
	return worldLayout_;
}

std::vector<sVkDescriptorSetLayout> ResourceManager::getBuiltInLayouts() const
{
	return {worldLayout_};
}

sVkDescriptorPool ResourceManager::getBuiltInPool() const
{
	return builtInPool_;
}

QueuedOperations &ResourceManager::getQueuedOperations() const
{
	return *queuedOperations_;
}

std::shared_ptr<CubA4::resources::IResource> ResourceManager::getCache(resources::Path path) const
{
	using namespace resources;
	return core_->getResourcesManager()->edit(Path("cache") / Path("render") / Path("vulkan") / path);
}

void ResourceManager::createBuildInDescriptorSetLayouts()
{
	VkDescriptorSetLayoutBinding worldInfo = {};
	//Matrix info
	worldInfo.binding = 0;
	worldInfo.descriptorCount = 1;
	worldInfo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	worldInfo.stageFlags = VK_SHADER_STAGE_ALL;
	worldLayout_ = createSetFromBindings(&worldInfo, 1, "World info layout set");
}

void ResourceManager::createBuiltInDescriptorPool()
{
	std::vector<VkDescriptorPoolSize> sizes;

	VkDescriptorPoolCreateInfo poolCreateInfo = {};
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	poolCreateInfo.maxSets = 1;

	VkDescriptorPoolSize uniforms;
	uniforms.descriptorCount = 1;
	uniforms.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

	sizes.push_back(uniforms);

	poolCreateInfo.poolSizeCount = static_cast<uint32_t>(sizes.size());
	poolCreateInfo.pPoolSizes = sizes.data();

	VkDescriptorPool pool = {};

	if (vkCreateDescriptorPool(device_->getDevice(), &poolCreateInfo, nullptr, &pool) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}

	device_->getMarker().setName(pool, "Builtin pool");

	std::function<void(VkDescriptorPool pool)> deleter = [dev = device_](VkDescriptorPool pool)
	{
		vkDestroyDescriptorPool(dev->getDevice(), pool, nullptr);
	};

	builtInPool_ = createSharedVulkanObject(pool, deleter);
}

sVkDescriptorSetLayout ResourceManager::createSetFromBindings(const VkDescriptorSetLayoutBinding *bindings, size_t count, const char *name)
{
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
	descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(count);
	descriptorSetLayoutInfo.pBindings = bindings;
	VkDescriptorSetLayout layout = {};
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &layout) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return {};
	}
	device_->getMarker().setName(layout, name);

	std::function<void(VkDescriptorSetLayout)> deleter = [dev = device_](VkDescriptorSetLayout layout)
	{
		vkDestroyDescriptorSetLayout(dev->getDevice(), layout, nullptr);
	};
	return createSharedVulkanObject(layout, deleter);
}