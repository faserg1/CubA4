#include "./TextureImporter.hpp"
#include <png.h>
using namespace CubA4::render::engine::material;

TextureImporter::TextureImporter()
{
	
}

TextureImporter::~TextureImporter()
{
	
}

std::shared_ptr<Texture> TextureImporter::importPng()
{
	png_structp png_ptr = nullptr;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	return {};
}