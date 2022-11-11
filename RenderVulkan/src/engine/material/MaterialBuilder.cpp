#include "./MaterialBuilder.hpp"
#include "./MaterialLayout.hpp"
#include "./Material.hpp"
#include "./Texture.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialBuilder::MaterialBuilder(std::shared_ptr<const Device> device, std::shared_ptr<const DescriptorPool> pool,
	std::shared_ptr<const IMaterialLayout> layout, VkSampler sampler) :
		device_(device), pool_(pool), layout_(layout), sampler_(sampler)
{
	
}

MaterialBuilder::~MaterialBuilder()
{
	
}

void MaterialBuilder::addTexture(std::shared_ptr<const ITexture> texture)
{
	textures_.push_back(texture);
}

std::shared_ptr<const IMaterial> MaterialBuilder::build()
{
	auto layout = std::dynamic_pointer_cast<const MaterialLayout>(layout_);
	auto set = createSet();
	writeSet(set);
	return std::make_shared<Material>(layout, textures_, set, sampler_);
}

VkDescriptorSet MaterialBuilder::createSet()
{
	VkDescriptorSet set;
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = pool_->get();
	allocInfo.descriptorSetCount = 1;
	auto layout = std::dynamic_pointer_cast<const MaterialLayout>(layout_)->getLayout();
	VkDescriptorSetLayout layouts[] = { layout->get() };
	allocInfo.pSetLayouts = layouts;
	if (vkAllocateDescriptorSets(device_->getDevice(), &allocInfo, &set) != VK_SUCCESS)
	{
		// TODO: Exception
		return {};
	}
	return set;
}

void MaterialBuilder::writeSet(VkDescriptorSet set)
{
	VkWriteDescriptorSet writeSet = {};
	writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeSet.descriptorCount = static_cast<uint32_t>(textures_.size());
	writeSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	writeSet.dstBinding = 2;
	writeSet.dstSet = set;
	
	std::vector<VkDescriptorImageInfo> imageInfos(textures_.size());
	for (uint32_t i = 0; i < textures_.size(); i++)
	{
		auto &imgInfo = imageInfos[i];
		auto texture = std::dynamic_pointer_cast<const Texture>(textures_[i]);
		imgInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imgInfo.imageView = texture->getTextureView();
		imgInfo.sampler = sampler_;
	}

	writeSet.pImageInfo = imageInfos.data();
	vkUpdateDescriptorSets(device_->getDevice(), 1, &writeSet, 0, nullptr);
}