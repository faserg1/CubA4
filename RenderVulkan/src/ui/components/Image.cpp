#include <ui/components/Image.hpp>
#include <ui/utils/RectConvert.hpp>
using namespace CubA4::render::ui;

Image::Image(std::shared_ptr<const ITexture> texture, sk_sp<SkImage> image) :
	texture_(texture), image_(image)
{

}

void Image::setMode(ImageMode mode)
{
	mode_ = mode;
}

ImageMode Image::getMode() const
{
	return mode_;
}

void Image::setImageOffsets(float x, float y)
{
	dstRect_.fLeft = x;
	dstRect_.fTop = y;
}

void Image::setImageSize(const Rect &sizeRect)
{
	dstRect_ = toSkia(sizeRect);
}

void Image::setImageRect(const Rect &srcRect, const Rect &dstRect)
{
	dstRect_ = toSkia(dstRect);
	srcRect_ = toSkia(srcRect);
}

void Image::setImageNinePath(const RectI &centerRect, const Rect &dstRect)
{
	dstRect_ = toSkia(dstRect);
	centerRect_ = toSkia(centerRect);
}

void Image::draw(SkCanvas *parentCanvas)
{
	if (!visibility_)
		return;
	switch (mode_)
	{
	case ImageMode::Default:
		parentCanvas->drawImage(image_, dstRect_.fLeft, dstRect_.fTop);
		break;
	case ImageMode::Size:
		parentCanvas->drawImageRect(image_, dstRect_, samplingOptions_);
		break;
	case ImageMode::Rect:
		parentCanvas->drawImageRect(image_, srcRect_, dstRect_, samplingOptions_, &paint_, srcRectConstraint_);
		break;
	case ImageMode::NinePath:
		parentCanvas->drawImageNine(image_.get(), centerRect_, dstRect_, filterMode_);
		break;
	}
}