#pragma once

#include <memory>
#include <engine/material/IMaterial.hpp>
#include <vector>
#include <vulkan/vulkan.h>

namespace CubA4::render::engine::material
{
	class MaterialLayout;
	class ITexture;

	class Material :
		public virtual IMaterial
	{
	public:
		explicit Material(std::shared_ptr<const MaterialLayout> layout, std::vector<std::shared_ptr<const ITexture>> textures,
			VkDescriptorSet set, VkSampler sampler);
		~Material();

		std::shared_ptr<const MaterialLayout> getLayout() const;
		bool apply(VkCommandBuffer cmd) const;
	protected:
	private:
		const std::shared_ptr<const MaterialLayout> layout_;
		const std::vector<std::shared_ptr<const ITexture>> textures_;
		const VkDescriptorSet set_;
		const VkSampler sampler_;
	};
}
