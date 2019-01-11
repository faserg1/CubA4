#include "./ResourceManager.hpp"
#include "../vulkan/Device.hpp"
#include "../VulkanInfoConst.hpp"
#include <vector>
#include <ICore.hpp>
#include <cache/ICacheManager.hpp>
using namespace CubA4::core;
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

ResourceManager::ResourceManager(std::shared_ptr<const Device> device, std::shared_ptr<const ICore> core) :
	device_(device), core_(core)
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

sVkDescriptorSetLayout ResourceManager::getChunkLayout() const
{
	return chunkLayout_;
}

sVkDescriptorPool ResourceManager::getBuiltInPool() const
{
	return builtInPool_;
}

std::shared_ptr<cache::ICache> ResourceManager::getCache() const
{
	auto cacheManager = core_->getCacheManager();
	return cacheManager->getResources(cache::CacheType::Render, RenderEngineId);
}

void ResourceManager::createBuildInDescriptorSetLayouts()
{
	VkDescriptorSetLayoutBinding worldInfo = {}, chunkInfo = {};
	//Matrix info
	worldInfo.binding = 0;
	worldInfo.descriptorCount = 1;
	worldInfo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	worldInfo.stageFlags = VK_SHADER_STAGE_ALL;
	//Chunk range info
	chunkInfo.binding = 1;
	chunkInfo.descriptorCount = 1;
	chunkInfo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	chunkInfo.stageFlags = VK_SHADER_STAGE_ALL;

	worldLayout_ = createSetFromBindings(&worldInfo, 1, "World info layout set");
	chunkLayout_ = createSetFromBindings(&chunkInfo, 1, "Chunk info layout set");
}

void ResourceManager::createBuiltInDescriptorPool()
{
	std::vector<VkDescriptorPoolSize> sizes;

	VkDescriptorPoolCreateInfo poolCreateInfo = {};
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
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

	builtInPool_ = util::createSharedVulkanObject(pool, deleter);
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
	return util::createSharedVulkanObject(layout, deleter);
}