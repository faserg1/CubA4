#pragma once

#include <memory>
#include <engine/material/ITextureImporter.hpp>
#include <vulkan/vulkan.h>

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

					std::shared_ptr<ITexture> importFromPng(std::shared_ptr<const CubA4::resources::IResource> resource) const override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<memory::MemoryAllocator> memoryAllocator_;
					const std::shared_ptr<memory::MemoryManager> memoryManager_;
					const std::shared_ptr<memory::MemoryHelper> memoryHelper_;
				private:
					std::shared_ptr<ITexture> internalImportFromPng(void *pngStruct, const char *debugName) const;
					static uint32_t countMipMapLevels(uint32_t width, uint32_t height);
					std::vector<VkBufferImageCopy> makeMipLevels(void *data, int bitDepth, uint8_t channelCount, uint32_t levelCount, uint32_t width, uint32_t height) const;
					void makeNextLevel(void *src, void *dst, int bitDepth, uint8_t channelCount, uint32_t dstWidth, uint32_t dstHeight) const;
				};
			}
		}
	}
}

