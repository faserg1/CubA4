#include <engine/material/TexturesDescriptorPool.hpp>
using namespace CubA4::render::engine::material;

TexturesDescriptorPool::TexturesDescriptorPool(std::shared_ptr<const vulkan::Device> device) :
	DescriptorPool(device)
{
	createPool();	
}

TexturesDescriptorPool::~TexturesDescriptorPool()
{
	
}

uint32_t TexturesDescriptorPool::getMaxSetCount() const
{
	// TODO: adjust?
	return 1000;
}

std::vector<VkDescriptorPoolSize> TexturesDescriptorPool::getPoolSizes() const
{
	std::vector<VkDescriptorPoolSize> sizes;
	VkDescriptorPoolSize textures;
	textures.descriptorCount = 1000; // TODO: adjust?
	textures.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

	sizes.push_back(textures);
	return std::move(sizes);
}