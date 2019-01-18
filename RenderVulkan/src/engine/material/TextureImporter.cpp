#include "./TextureImporter.hpp"
#include "./Texture.hpp"
#include <png.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include <stdexcept>
#include <filesystem/IAbstractResource.hpp>
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include "../memory/MemoryAllocator.hpp"
#include "../memory/MemoryManager.hpp"
#include "../memory/MemoryHelper.hpp"
#include "../memory/MemoryPart.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::engine::memory;
using namespace CubA4::core::filesystem;
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

std::shared_ptr<ITexture> TextureImporter::importFromPng(std::shared_ptr<const IAbstractResource> resource) const
{
	png_byte sig[PngSignatureLenght];
	auto readed = resource->loadIn(sig, PngSignatureLenght, 0);
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
		std::shared_ptr<const IAbstractResource> resource;
		size_t offset;
	} res{resource, 0};
	png_set_read_fn(png_ptr, &res, [](png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead) -> void
	{
		auto resData = reinterpret_cast<resourceData*>(png_get_io_ptr(png_ptr));
		auto readed = resData->resource->loadIn(outBytes, byteCountToRead, resData->offset);
		if (readed != byteCountToRead)
		{
			// TODO: png_error()
			return;
		}
		resData->offset += byteCountToRead;
	});
	png_set_sig_bytes(png_ptr, 0);

	return internalImportFromPng(png_ptr);
}

std::shared_ptr<ITexture> TextureImporter::importFromPng(void *ptr, size_t size) const
{
	auto *data = static_cast<png_const_bytep>(ptr);
	if (!png_check_sig(data, PngSignatureLenght))
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

	struct rawData
	{
		void *ptr;
		size_t offset;
		size_t size;
	} rd = {ptr, 0, size};
	png_set_read_fn(png_ptr, &rd, [](png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead) -> void
	{
		auto data = reinterpret_cast<rawData*>(png_get_io_ptr(png_ptr));
		if (data->offset + byteCountToRead > data->size)
		{
			// TODO: png_error()
			return;
		}
		memcpy(outBytes, reinterpret_cast<char*>(data->ptr) + data->offset, byteCountToRead);
		data->offset += byteCountToRead;
	});
	png_set_sig_bytes(png_ptr, 0);

	return internalImportFromPng(png_ptr);
}

std::shared_ptr<ITexture> TextureImporter::internalImportFromPng(void *pngStruct) const
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
	uint8_t bits_per_pixel = bitDepth * channels_count;
	uint8_t bytes_per_pixel = bits_per_pixel / 8;
	size_t image_size = bytes_per_pixel * width * height;

	// Prepare resources for loaded texture

	VkBuffer tempBuffer = {};
	VkBufferCreateInfo tempBufferInfo = {};
	tempBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	tempBufferInfo.size = image_size;
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
					if (!data[write_byte + 3])
						data[write_byte + 3] = 1;
					data[write_byte + 3] = -data[write_byte + 3]; //alpha channel
				}

				byteIndex += bytes_per_pixel;
			}
			else if (bitDepth == 32)
			{
				// TODO: [OOKAMI] Забить или упасть?
			}
		}
	}

	// unmap memory
	tempBufferMappedPtr.reset();

	// create device image

	VkImage texture;
	VkImageCreateInfo textureInfo = {};
	textureInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	textureInfo.extent.depth = 1;
	textureInfo.extent.width = width;
	textureInfo.extent.height = height;
	textureInfo.mipLevels = 1;
	textureInfo.arrayLayers = 1;
	textureInfo.imageType = VK_IMAGE_TYPE_2D;
	textureInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	textureInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	textureInfo.tiling = VK_IMAGE_TILING_LINEAR;
	textureInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	textureInfo.samples = VK_SAMPLE_COUNT_1_BIT;

	if (vkCreateImage(device_->getDevice(), &textureInfo, nullptr, &texture) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, destroy temp buffer
		return {};
	}

	VkMemoryRequirements textureMemReq;
	vkGetImageMemoryRequirements(device_->getDevice(), texture, &textureMemReq);
	auto memoryPart = memoryManager_->allocatePart(textureMemReq.size, textureMemReq.alignment, textureMemReq.memoryTypeBits);
	if (vkBindImageMemory(device_->getDevice(), texture, memoryPart->getMemory()->getMemory(), memoryPart->getOffset()) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, destroy image
		return {};
	}
	// copy buffer to image

	VkBufferImageCopy fullTextureRegion = {};
	fullTextureRegion.imageExtent = textureInfo.extent;
	fullTextureRegion.imageSubresource.layerCount = 1;
	fullTextureRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

	VkImageSubresourceRange subResRange = {};
	subResRange.layerCount = 1;
	subResRange.levelCount = 1;
	subResRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

	auto copyFucture = memoryHelper_->copyBufferToImage(tempBuffer, texture, { fullTextureRegion }, VK_IMAGE_LAYOUT_UNDEFINED, subResRange);
	copyFucture.wait();

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

	return std::make_shared<Texture>(device_, texture, textureView, memoryPart);
}