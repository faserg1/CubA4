#include "./TextureImporter.hpp"
#include "./Texture.hpp"
#include <png.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <resources/IResource.hpp>
#include <engine/material/TextureHelper.hpp>
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../memory/MemoryAllocator.hpp"
#include "../memory/MemoryManager.hpp"
#include "../memory/MemoryHelper.hpp"
#include "../memory/MemoryPart.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::engine::memory;
using namespace CubA4::resources;
using namespace CubA4::render::vulkan;

constexpr const unsigned PngSignatureLenght = 8;

TextureImporter::TextureImporter(std::shared_ptr<const Device> device) :
	device_(device),
	memoryAllocator_(std::make_shared<MemoryAllocator>(device)),
	memoryManager_(std::make_shared<MemoryManager>(device)),
	memoryHelper_(std::make_shared<MemoryHelper>(device))
{
	
}

TextureImporter::~TextureImporter()
{
	
}

std::shared_ptr<ITexture> TextureImporter::importFromPng(std::shared_ptr<const IResource> resource) const
{
	png_byte sig[PngSignatureLenght];
	auto readed = resource->copyIn(sig, PngSignatureLenght, 0);
	if (readed != PngSignatureLenght || !png_check_sig(sig, PngSignatureLenght))
	{
		// TODO: [OOKAMI] Exception
		return {};
	}
	png_structp png_ptr = nullptr;
	png_error_ptr errorHandler = [](png_structp png_ptr, png_const_charp text)
	{
		// TODO: [OOKAMI] Normal exception
		throw std::runtime_error(text);
	};
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, errorHandler, nullptr);

	// RAII-like
	struct PngReadStructGuard
	{
		png_structp &readStruct;
		~PngReadStructGuard()
		{
			png_destroy_read_struct(&readStruct, nullptr, nullptr);
		}
	} guard{ png_ptr };

	// reader

	struct resourceData
	{
		std::shared_ptr<const IResource> resource;
		size_t offset;
	} res{resource, 0};
	png_set_read_fn(png_ptr, &res, [](png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead) -> void
	{
		auto resData = reinterpret_cast<resourceData*>(png_get_io_ptr(png_ptr));
		auto readed = resData->resource->copyIn(outBytes, byteCountToRead, resData->offset);
		if (readed != byteCountToRead)
		{
			// TODO: png_error()
			return;
		}
		resData->offset += byteCountToRead;
	});
	png_set_sig_bytes(png_ptr, 0);

	return internalImportFromPng(png_ptr, resource->path().c_str());
}

std::shared_ptr<ITexture> TextureImporter::internalImportFromPng(void *pngStruct, const char *debugName) const
{
	auto *png_ptr = reinterpret_cast<png_structp>(pngStruct);

	// Prepare info from png

	auto info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		return {};
	png_read_info(png_ptr, info_ptr);
	png_uint_32 width = 0;
	png_uint_32 height = 0;
	int bitDepth = 0;
	int colorType = -1;
	int interlace_type = -1;
	auto retval = png_get_IHDR(png_ptr, info_ptr,
		&width,
		&height,
		&bitDepth,
		&colorType,
		&interlace_type, nullptr, nullptr);
	if (retval != 1)
		return {};
	uint8_t channels_count;
	switch (colorType)
	{
	case PNG_COLOR_TYPE_RGB:
		channels_count = 3;
		break;
	case PNG_COLOR_TYPE_RGBA:
		channels_count = 4;
		break;
	default:
		// TODO: Exception: unsupported format
		return {};
	}
	if (interlace_type == PNG_INTERLACE_ADAM7)
		// TODO: Exception: unsupported format
		return {};
	const uint8_t bits_per_pixel = bitDepth * channels_count;
	const uint8_t bytes_per_pixel = bits_per_pixel / 8;
	// size_t image_size = bytes_per_pixel * width * height;

	const auto isPowerOfTwo = [](uint32_t n) -> bool {return (n>0 && ((n & (n-1)) == 0)); };

	auto mipLevels = isPowerOfTwo(width) && isPowerOfTwo(height) ? countMipMapLevels(width, height) : 1;
	size_t imageSize = 0;
	{
		auto currentWidth = width;
		auto currentHeight = height;
		
		for (uint32_t level = 0; level < mipLevels; level++, currentWidth /= 2, currentHeight /= 2)
			imageSize += bytes_per_pixel * currentWidth * currentHeight;
	}
	

	// Prepare resources for loaded texture

	VkBuffer tempBuffer = {};
	VkBufferCreateInfo tempBufferInfo = {};
	tempBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	tempBufferInfo.size = imageSize; // + mip levels
	tempBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

	if (vkCreateBuffer(device_->getDevice(), &tempBufferInfo, nullptr, &tempBuffer) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception
		return {};
	}

	VkMemoryRequirements tempBufferReq;
	vkGetBufferMemoryRequirements(device_->getDevice(), tempBuffer, &tempBufferReq);

	auto tempBufferMemory = memoryAllocator_->allocateAndBind(tempBuffer, MemoryAllocationPrefered::Host);
	auto tempBufferMappedPtr = tempBufferMemory->map(0, VK_WHOLE_SIZE);

	png_bytep data = reinterpret_cast<png_bytep>(tempBufferMappedPtr.get());

	// Load in resource

	constexpr const bool invertRows = false;
	constexpr const bool invertColumns = false;

	const png_size_t bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
	std::vector<png_byte> rowDataVector(bytesPerRow);
	png_bytep rowData = rowDataVector.data();
	uint64_t result_bits_per_pixel = channels_count * 8;
	for (uint64_t rowIdx = 0; rowIdx < height; ++rowIdx)
	{
		png_read_row(png_ptr, (png_bytep)rowData, nullptr);

		const uint64_t rowOffset = (invertRows ? (((height - 1) - rowIdx) * width) : (rowIdx * width));

		uint64_t byteIndex = 0;
		for (uint64_t colIdx = 0; colIdx < width; ++colIdx)
		{
			if (bitDepth == 8)
			{
				size_t write_byte = (invertColumns ? ((rowOffset + ((width - 1) - colIdx)) * bytes_per_pixel) : ((rowOffset + colIdx) * bytes_per_pixel));
				memcpy(&data[write_byte], &rowData[byteIndex], bytes_per_pixel);

				if (channels_count == 4)
				{
					/*if (!data[write_byte + 3])
						data[write_byte + 3] = 1;*/
					// rewert alpha channel ???
					// data[write_byte + 3] = -data[write_byte + 3];
				}

				byteIndex += bytes_per_pixel;
			}
			else if (bitDepth == 32)
			{
				// TODO: [OOKAMI] Забить или упасть?
			}
		}
	}

	auto regions = makeMipLevels(tempBufferMappedPtr.get(), bitDepth, channels_count, mipLevels, width, height);

	// unmap memory
	tempBufferMappedPtr.reset();

	// create device image

	VkImage texture;
	VkImageCreateInfo textureInfo = {};
	textureInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	textureInfo.extent.depth = 1;
	textureInfo.extent.width = width;
	textureInfo.extent.height = height;
	textureInfo.mipLevels = mipLevels;
	textureInfo.arrayLayers = 1;
	textureInfo.imageType = VK_IMAGE_TYPE_2D;
	textureInfo.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	textureInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	textureInfo.tiling = VK_IMAGE_TILING_OPTIMAL; // ???
	textureInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	textureInfo.samples = VK_SAMPLE_COUNT_1_BIT;

	if (vkCreateImage(device_->getDevice(), &textureInfo, nullptr, &texture) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, destroy temp buffer
		return {};
	}

	device_->getMarker().setName(texture, debugName);

	VkMemoryRequirements textureMemReq;
	vkGetImageMemoryRequirements(device_->getDevice(), texture, &textureMemReq);
	auto memoryPart = memoryManager_->allocatePart(textureMemReq.size, textureMemReq.alignment, textureMemReq.memoryTypeBits);
	if (vkBindImageMemory(device_->getDevice(), texture, memoryPart->getMemory()->getMemory(), memoryPart->getOffset()) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, destroy image
		return {};
	}
	// copy buffer to image

	VkImageSubresourceRange subResRange = {};
	subResRange.layerCount = 1;
	subResRange.levelCount = mipLevels;
	subResRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

	auto copyFuture = memoryHelper_->copyBufferToImage(tempBuffer, texture, regions, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, subResRange);
	copyFuture.wait();

	// delete temp buffer

	vkDestroyBuffer(device_->getDevice(), tempBuffer, nullptr);

	// create a view

	VkImageView textureView;
	VkImageViewCreateInfo imageViewCreateInfo = {};
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCreateInfo.format = textureInfo.format;
	imageViewCreateInfo.image = texture;
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCreateInfo.subresourceRange = subResRange;
	if (vkCreateImageView(device_->getDevice(), &imageViewCreateInfo, nullptr, &textureView) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, destroy image
		return {};
	}

	// return texture

	return std::make_shared<Texture>(device_, texture, textureView, memoryPart, textureInfo);
}

uint32_t TextureImporter::countMipMapLevels(uint32_t width, uint32_t height)
{
	return static_cast<uint32_t>(floor(log2(std::max(width, height))) + 1);
}

std::vector<VkBufferImageCopy> TextureImporter::makeMipLevels(void *data, int bitDepth, uint8_t channelCount, uint32_t levelCount, uint32_t width, uint32_t height) const
{
	const uint8_t bits_per_pixel = bitDepth * channelCount;
	const uint8_t bytes_per_pixel = bits_per_pixel / 8;

	auto prevWidth = width;
	auto prevHeight = height;
	auto currentWidth = width;
	auto currentHeight = height;

	size_t previousDataOffset = 0;

	std::vector<VkBufferImageCopy> regions(levelCount);
	regions[0] = {};
	regions[0].imageExtent.depth = 1;
	regions[0].imageExtent.width = width;
	regions[0].imageExtent.height = height;
	regions[0].imageSubresource.layerCount = 1;
	regions[0].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	
	for (uint32_t level = 0; level < levelCount; level++, currentWidth /= 2, currentHeight /= 2)
	{
		if (level == 0)
			continue;
		size_t offset = bytes_per_pixel * prevWidth * prevHeight;
		auto currentOffset = previousDataOffset + offset;

		regions[level] = {};
		regions[level].imageExtent.depth = 1;
		regions[level].imageExtent.width = currentWidth;
		regions[level].imageExtent.height = currentHeight;
		regions[level].imageSubresource.layerCount = 1;
		regions[level].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		regions[level].imageSubresource.mipLevel = level;
		regions[level].bufferOffset = currentOffset;
		
		void *prevData = reinterpret_cast<void*>(reinterpret_cast<size_t>(data) + previousDataOffset);
		void *currentData = reinterpret_cast<void*>(reinterpret_cast<size_t>(data) + currentOffset);

		makeNextLevel(prevData, currentData, bitDepth, channelCount, currentWidth, currentHeight);

		prevWidth = currentWidth;
		prevHeight = currentHeight;
		previousDataOffset += offset;
	}
	return std::move(regions);
}

void TextureImporter::makeNextLevel(void *src, void *dst, int bitDepth, uint8_t channelCount, uint32_t dstWidth, uint32_t dstHeight) const
{
	const uint8_t bits_per_pixel = bitDepth * channelCount;
	const uint8_t bytesPerPixel = bits_per_pixel / 8;
	const size_t bytesPerDstRow = bytesPerPixel * dstWidth;
	const size_t bytesPerSrcRow = bytesPerPixel * dstWidth * 2;

	struct RGBA
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	for (uint32_t y = 0; y < dstHeight; y++)
	{
		for (uint32_t x = 0; x < dstWidth; x++)
		{
			auto offsetDst = (bytesPerPixel * x) + (bytesPerDstRow * y);
			auto dstPixel = reinterpret_cast<RGBA*>(reinterpret_cast<size_t>(dst) + offsetDst);

			uint32_t srcX = x * 2;
            uint32_t srcY = y * 2;

			std::array<RGBA*, 4> srcPixels;

			auto getSourcePixelData = [src, bytesPerPixel, bytesPerSrcRow](uint32_t x, uint32_t y) -> RGBA * {
				auto offsetSrc = (bytesPerPixel * x) + (bytesPerSrcRow * y);
           		return reinterpret_cast<RGBA *>(reinterpret_cast<size_t>(src) + offsetSrc);
			};
			
			for (uint8_t px = 0; px < 4; px++)
			{
				auto sx = srcX + (px % 2);
				auto sy = srcY + (px >= 2 ? 1 : 0);
				srcPixels[px] = getSourcePixelData(sx, sy);
			}

			dstPixel->r = blendNoAlpha({srcPixels[0]->r, srcPixels[1]->r, srcPixels[2]->r, srcPixels[3]->r});
			dstPixel->g = blendNoAlpha({srcPixels[0]->g, srcPixels[1]->g, srcPixels[2]->g, srcPixels[3]->g});
			dstPixel->b = blendNoAlpha({srcPixels[0]->b, srcPixels[1]->b, srcPixels[2]->b, srcPixels[3]->b});
			dstPixel->a = srcPixels[0]->a; // TODO
		}
	}
}

