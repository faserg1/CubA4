#pragma once

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
			namespace memory
			{
				class MemoryHelper;
				class MemoryManager;
				class MemoryAllocator;
			}

			namespace material
			{
				class Texture;

				class TextureImporter :
					public virtual ITextureImporter
				{
				public:
					explicit TextureImporter(std::shared_ptr<const vulkan::Device> device);
					~TextureImporter();

					std::shared_ptr<ITexture> importFromPng(std::shared_ptr<const CubA4::core::resources::IResource> resource) const override;
					std::shared_ptr<ITexture> importFromPng(void *ptr, size_t size) const override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<memory::MemoryAllocator> memoryAllocator_;
					const std::shared_ptr<memory::MemoryManager> memoryManager_;
					const std::shared_ptr<memory::MemoryHelper> memoryHelper_;
				private:
					std::shared_ptr<ITexture> internalImportFromPng(void *pngStruct) const;
				};
			}
		}
	}
}

