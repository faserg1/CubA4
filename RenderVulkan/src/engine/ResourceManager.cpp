#include "./ResourceManager.hpp"
#include "../vulkan/Device.hpp"
#include <vector>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

ResourceManager::ResourceManager(std::shared_ptr<const Device> device) :
	device_(device)
{
	createBuildInDescriptorSetLayout();
	createBuiltInDescriptorPool();
}

ResourceManager::~ResourceManager()
{

}

sVkDescriptorSetLayout ResourceManager::getBuiltInLayout() const
{
	return builtInLayout_;
}

sVkDescriptorPool ResourceManager::getBuiltInPool() const
{
	return builtInPool_;
}

void ResourceManager::createBuildInDescriptorSetLayout()
{
	VkDescriptorSetLayoutBinding bindingInfos[1] = {};
	//Matrix info
	bindingInfos[0].binding = 0;
	bindingInfos[0].descriptorCount = 1;
	bindingInfos[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindingInfos[0].stageFlags = VK_SHADER_STAGE_ALL;
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
	descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutInfo.bindingCount = 1;
	descriptorSetLayoutInfo.pBindings = bindingInfos;
	VkDescriptorSetLayout layout = {};
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &layout) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}
	device_->getMarker().setName(layout, "BuiltIn Layout");

	std::function<void(VkDescriptorSetLayout)> deleter = [dev = device_](VkDescriptorSetLayout layout)
	{
		vkDestroyDescriptorSetLayout(dev->getDevice(), layout, nullptr);
	};
	builtInLayout_ = util::createSharedVulkanObject(layout, deleter);
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