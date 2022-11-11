#include "./Material.hpp"
#include <engine/material/MaterialLayout.hpp>
#include <engine/material/Texture.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/Pipeline.hpp>
using namespace CubA4::render::engine::material;

Material::Material(std::shared_ptr<const MaterialLayout> layout, std::vector<std::shared_ptr<const ITexture>> textures,
	VkDescriptorSet set, VkSampler sampler) :
		layout_(layout), textures_(std::move(textures)), set_(set), sampler_(sampler)
{
	
}

Material::~Material()
{
	
}

std::shared_ptr<const MaterialLayout> Material::getLayout() const
{
	return layout_;
}

bool Material::apply(VkCommandBuffer cmd) const
{
	layout_->getPipeline()->bind(cmd);
	vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, layout_->getPipeline()->getLayout(), 1, 1, &set_ , 0, nullptr);
	return true;
}
