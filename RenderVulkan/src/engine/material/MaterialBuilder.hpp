#pragma once

#include <memory>
#include <engine/material/IMaterialBuilder.hpp>
#include <engine/material/DescriptorPool.hpp>
#include <vector>
#include <vulkan/vulkan.h>
#include "../../vulkan/util/VulkanHandlerContainer.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			namespace material
			{
				class IMaterialLayout;
				class ITexture;

				class MaterialBuilder :
					public virtual IMaterialBuilder
				{
				public:
					explicit MaterialBuilder(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const DescriptorPool> pool,
						std::shared_ptr<const IMaterialLayout> layout, VkSampler sampler);
					~MaterialBuilder();

					std::shared_ptr<const IMaterial> build() override;
					void addTexture(std::shared_ptr<const ITexture> texture) override;
				protected:
					VkDescriptorSet createSet();
					void writeSet(VkDescriptorSet set);
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const DescriptorPool> pool_;
					const std::shared_ptr<const IMaterialLayout> layout_;
					std::vector<std::shared_ptr<const ITexture>> textures_;
					const VkSampler sampler_;
				};
			}
		}
	}
}

