#include "./ResourceManager.hpp"
#include "../vulkan/Device.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

ResourceManager::ResourceManager(std::shared_ptr<const Device> device) :
	device_(device)
{
	createBuildInDescriptorSetLayout();
}

ResourceManager::~ResourceManager()
{
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
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &builtInLayout_) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}
}

void ResourceManager::destroyBuildInDescriptorSetLayout()
{
	vkDestroyDescriptorSetLayout(device_->getDevice(), builtInLayout_, nullptr);
}