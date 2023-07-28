#pragma once

#include <memory>
#include <ui/components/IImage.hpp>
#include <ui/components/BaseComponent.hpp>
#include <engine/material/ITexture.hpp>
#include <skia/include/core/SkImage.h>

namespace CubA4::render::ui
{
	class Image : public BaseComponent, public virtual IImage
	{
		using ITexture = CubA4::render::engine::material::ITexture;
	public:
		Image(std::shared_ptr<const ITexture> texture, sk_sp<SkImage> image);

		void setMode(ImageMode mode) override;
		ImageMode getMode() const override;

		void setImageOffsets(float x, float y) override;
		void setImageSize(const Rect &sizeRect) override;
		void setImageRect(const Rect &srcRect, const Rect &dstRect) override;
		void setImageNinePath(const RectI &centerRect, const Rect &dstRect) override;

		void draw(SkCanvas *parentCanvas) override;
	private:
		std::shared_ptr<const ITexture> texture_;
		sk_sp<SkImage> image_;

		ImageMode mode_ = ImageMode::Default;
		SkRect srcRect_;
		SkIRect centerRect_;
		SkRect dstRect_;

		SkPaint paint_;
		SkCanvas::SrcRectConstraint srcRectConstraint_ = SkCanvas::SrcRectConstraint::kStrict_SrcRectConstraint;
		SkSamplingOptions samplingOptions_;
		SkFilterMode filterMode_ = SkFilterMode::kNearest;
	};
}