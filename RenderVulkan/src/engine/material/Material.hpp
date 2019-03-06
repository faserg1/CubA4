#ifndef RENDERVULKAN_MATERIAL_HPP
#define RENDERVULKAN_MATERIAL_HPP

#include <memory>
#include <engine/material/IMaterial.hpp>
#include <vector>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class MaterialLayout;
				class ITexture;

				class Material :
					public virtual IMaterial
				{
				public:
					explicit Material(std::shared_ptr<const MaterialLayout> layout, std::vector<std::shared_ptr<const ITexture>> textures, VkDescriptorSet set);
					~Material();

					std::shared_ptr<const MaterialLayout> getLayout() const;
					VkDescriptorSet getDescriptorSet() const;
				protected:
				private:
					const std::shared_ptr<const MaterialLayout> layout_;
					const std::vector<std::shared_ptr<const ITexture>> textures_;
					const VkDescriptorSet descriptorSet_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIAL_HPP
