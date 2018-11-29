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
	destroyBuiltInDescriptorPool();
	destroyBuildInDescriptorSetLayout();
}

VkDescriptorSetLayout ResourceManager::getBuiltInLayout() const
{
	return builtInLayout_;
}

void ResourceManager::createBuildInDescriptorSetLayout()
{
	VkDescriptorSetLayoutBinding bindingInfos[2] = {};
	//Matrix info
	bindingInfos[0].binding = 0;
	bindingInfos[0].descriptorCount = 1;
	bindingInfos[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindingInfos[0].stageFlags = VK_SHADER_STAGE_ALL;
	//Instance info
	bindingInfos[1].binding = 1;
	bindingInfos[1].descriptorCount = 1;
	bindingInfos[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindingInfos[1].stageFlags = VK_SHADER_STAGE_ALL;
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
	descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutInfo.bindingCount = 2;
	descriptorSetLayoutInfo.pBindings = bindingInfos;
	VkDescriptorSetLayout layout = {};
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &layout) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}
	device_->getMarker().setName(layout, "BuiltIn Layout");
	auto dev = device_;
	builtInLayout_ = std::shared_ptr(layout, [dev](VkDescriptorSetLayout layout)
	{
		vkDestroyDescriptorSetLayout(dev->getDevice(), layout, nullptr);
	});
}

void ResourceManager::destroyBuildInDescriptorSetLayout()
{
	builtInLayout_.reset();
}

void ResourceManager::createBuiltInDescriptorPool()
{
	std::vector<VkDescriptorPoolSize> sizes;

	VkDescriptorPoolCreateInfo poolCreateInfo = {};
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolCreateInfo.maxSets = 1;
	
	VkDescriptorPoolSize uniforms;
	uniforms.descriptorCount = 2;
	uniforms.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

	sizes.push_back(uniforms);

	poolCreateInfo.poolSizeCount = static_cast<uint32_t>(sizes.size());
	poolCreateInfo.pPoolSizes = sizes.data();

	if (vkCreateDescriptorPool(device_->getDevice(), &poolCreateInfo, nullptr, &builtInPool_) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}

	device_->getMarker().setName(builtInPool_, "Builtin pool");
}

void ResourceManager::destroyBuiltInDescriptorPool()
{
	vkDestroyDescriptorPool(device_->getDevice(), builtInPool_, nullptr);
}
