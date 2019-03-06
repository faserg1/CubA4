#ifndef RENDERVULKAN_MATERIALBUILDER_HPP
#define RENDERVULKAN_MATERIALBUILDER_HPP

#include <memory>
#include <engine/material/IMaterialBuilder.hpp>
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
					explicit MaterialBuilder(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const IMaterialLayout> layout, vulkan::sVkDescriptorPool pool);
					~MaterialBuilder();

					std::shared_ptr<const IMaterial> build() override;
					void addTexture(std::shared_ptr<const ITexture> texture) override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const IMaterialLayout> layout_;
					const vulkan::sVkDescriptorPool pool_;
					std::vector<std::shared_ptr<const ITexture>> textures_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALBUILDER_HPP
