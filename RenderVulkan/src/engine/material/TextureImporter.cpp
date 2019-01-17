#include "./TextureImporter.hpp"
#include <png.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include <filesystem/IAbstractResource.hpp>
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::core::filesystem;
using namespace CubA4::render::vulkan;

constexpr const unsigned PngSignatureLenght = 8;

TextureImporter::TextureImporter(std::shared_ptr<const Device> device) :
	device_(device)
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
		// Exception
		return {};
	}
	png_structp png_ptr = nullptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

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
		// Exception
		return {};
	}
	png_structp png_ptr = nullptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

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

	// Load in resource

	return {};
}