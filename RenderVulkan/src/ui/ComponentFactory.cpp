#include <ui/ComponentFactory.hpp>
#include <ui/Image.hpp>
#include <ui/utils/ColorUtils.hpp>
#include <engine/material/Texture.hpp>
#include <skia/include/core/SkImage.h>
#include <skia/include/gpu/GrBackendSurface.h>
#include <skia/include/gpu/vk/GrVkTypes.h>
#include <skia/include/core/SkColorSpace.h>
using namespace CubA4::render::ui;


ComponentFactory::ComponentFactory(std::shared_ptr<const UISkContext> context) :
	context_(context)
{
	
}

std::shared_ptr<IImage> ComponentFactory::createImage(std::shared_ptr<const ITexture> iTexture)
{
	if (!iTexture)
		return {};
	auto texture = std::dynamic_pointer_cast<const CubA4::render::engine::material::Texture>(iTexture);
	if (!texture)
		return {};
	const auto &textureInfo = texture->getTextureInfo();
	GrVkImageInfo imageInfo {
		.fImage = texture->getTexture(),
		.fImageTiling = textureInfo.tiling,
		.fImageLayout = textureInfo.initialLayout,
		.fFormat = textureInfo.format,
		.fImageUsageFlags = textureInfo.usage,
		.fLevelCount = textureInfo.mipLevels
	};
	GrBackendTexture backendTexture(textureInfo.extent.width, textureInfo.extent.height, imageInfo);
	SkColorType colorType = getColorType(textureInfo.format);
	// TODO: Take from params
	auto alphaType = SkAlphaType::kUnpremul_SkAlphaType;
	auto colorSpace = SkColorSpace::MakeSRGB();
	auto image = SkImage::MakeFromTexture(context_->get().get(), backendTexture, GrSurfaceOrigin::kTopLeft_GrSurfaceOrigin, colorType, alphaType, colorSpace);
	return std::make_shared<Image>(iTexture, image);
}