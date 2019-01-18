#ifndef RENDERVULKAN_TEXTURE_HPP
#define RENDERVULKAN_TEXTURE_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <engine/material/ITexture.hpp>

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
			namespace memory
			{
				class IMemoryPart;
			}

			namespace material
			{
				class Texture :
					public virtual ITexture
				{
				public:
					explicit Texture(std::shared_ptr<const vulkan::Device> device, VkImage texture, VkImageView textureView, std::shared_ptr<const memory::IMemoryPart> part);
					~Texture();

					VkImage getTexture() const;
					VkImageView getTextureView() const;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const VkImage texture_;
					const VkImageView textureView_;
					const std::shared_ptr<const memory::IMemoryPart> memoryPart_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_TEXTURE_HPP
