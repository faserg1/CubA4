#ifndef RENDERVULKAN_TEXTUREIMPORTER_HPP
#define RENDERVULKAN_TEXTUREIMPORTER_HPP

#include <memory>
#include <engine/material/ITextureImporter.hpp>

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
				class Texture;

				class TextureImporter :
					public virtual ITextureImporter
				{
				public:
					explicit TextureImporter(std::shared_ptr<const vulkan::Device> device);
					~TextureImporter();

					std::shared_ptr<ITexture> importFromPng(std::shared_ptr<const CubA4::core::filesystem::IAbstractResource> resource) const override;
					std::shared_ptr<ITexture> importFromPng(void *ptr, size_t size) const override;
				protected:
				private:
					std::shared_ptr<const vulkan::Device> device_;
				private:
					std::shared_ptr<ITexture> internalImportFromPng(void *pngStruct) const;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_TEXTUREIMPORTER_HPP
