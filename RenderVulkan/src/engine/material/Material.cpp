#include "./Material.hpp"
using namespace CubA4::render::engine::material;

Material::Material(std::shared_ptr<const MaterialLayout> layout, std::vector<std::shared_ptr<const ITexture>> textures, VkDescriptorSet set) :
	layout_(layout), textures_(std::move(textures)), descriptorSet_(set)
{
	
}

Material::~Material()
{
	
}

std::shared_ptr<const MaterialLayout> Material::getLayout() const
{
	return layout_;
}

VkDescriptorSet Material::getDescriptorSet() const
{
	return descriptorSet_;
}