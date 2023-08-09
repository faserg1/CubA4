#include <ui/components/Image.hpp>
#include <ui/utils/RectConvert.hpp>
using namespace CubA4::render::ui;

Image::Image(std::shared_ptr<const ITexture> texture, sk_sp<SkImage> image) :
	texture_(texture), image_(image), calculator_(currentContext_)
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

void Image::setImageOffsets(const Expression &x, const Expression &y)
{
	dstRect_.left = x;
	dstRect_.top = y;
}

void Image::setImageSize(const Rect &sizeRect)
{
	dstRect_ = sizeRect;
}

void Image::setImageRect(const Rect &srcRect, const Rect &dstRect)
{
	dstRect_ = dstRect;
	srcRect_ = srcRect;
}

void Image::setImageNinePath(const RectI &centerRect, const Rect &dstRect)
{
	dstRect_ = dstRect;
	centerRect_ = toSkia(centerRect);
}

void Image::draw(SkCanvas *parentCanvas)
{
	if (!visibility_)
		return;
	switch (mode_)
	{
		case ImageMode::Default:
		{
			calculator_.calculate(dstRect_.left);
			calculator_.calculate(dstRect_.top);
			parentCanvas->drawImage(image_, dstRect_.left.getValue(), dstRect_.top.getValue());
			break;
		}
			
		case ImageMode::Size:
		{
			calculator_.calculate(dstRect_.left);
			calculator_.calculate(dstRect_.top);
			calculator_.calculate(dstRect_.right);
			calculator_.calculate(dstRect_.bottom);

			RectLD dstRectLd {
				.left = dstRect_.left.getValue(),
				.top = dstRect_.top.getValue(),
				.right = dstRect_.right.getValue(),
				.bottom = dstRect_.bottom.getValue(),
			};

			auto dstRect = toSkia(dstRectLd);

			parentCanvas->drawImageRect(image_, dstRect, samplingOptions_);
			break;
		}
			
		case ImageMode::Rect:
		{
			calculator_.calculate(dstRect_.left);
			calculator_.calculate(dstRect_.top);
			calculator_.calculate(dstRect_.right);
			calculator_.calculate(dstRect_.bottom);

			calculator_.calculate(srcRect_.left);
			calculator_.calculate(srcRect_.top);
			calculator_.calculate(srcRect_.right);
			calculator_.calculate(srcRect_.bottom);

			RectLD dstRectLd {
				.left = dstRect_.left.getValue(),
				.top = dstRect_.top.getValue(),
				.right = dstRect_.right.getValue(),
				.bottom = dstRect_.bottom.getValue(),
			};

			RectLD srcRectLd {
				.left = srcRect_.left.getValue(),
				.top = srcRect_.top.getValue(),
				.right = srcRect_.right.getValue(),
				.bottom = srcRect_.bottom.getValue(),
			};

			auto dstRect = toSkia(dstRectLd);
			auto srcRect = toSkia(srcRectLd);

			parentCanvas->drawImageRect(image_, srcRect, dstRect, samplingOptions_, &paint_, srcRectConstraint_);
			break;
		}
		case ImageMode::NinePath:
		{
			calculator_.calculate(dstRect_.left);
			calculator_.calculate(dstRect_.top);
			calculator_.calculate(dstRect_.right);
			calculator_.calculate(dstRect_.bottom);

			RectLD dstRectLd {
				.left = dstRect_.left.getValue(),
				.top = dstRect_.top.getValue(),
				.right = dstRect_.right.getValue(),
				.bottom = dstRect_.bottom.getValue(),
			};

			auto dstRect = toSkia(dstRectLd);

			parentCanvas->drawImageNine(image_.get(), centerRect_, dstRect, filterMode_);
			break;
		}
	}
}

void Image::updateContext(const Context &ctx)
{
	currentContext_ = ctx;
	srcRect_.left.markDirty();
	srcRect_.top.markDirty();
	srcRect_.right.markDirty();
	srcRect_.bottom.markDirty();

	dstRect_.left.markDirty();
	dstRect_.top.markDirty();
	dstRect_.right.markDirty();
	dstRect_.bottom.markDirty();

}