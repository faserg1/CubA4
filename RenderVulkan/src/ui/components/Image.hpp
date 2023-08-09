#pragma once

#include <memory>
#include <ui/components/IImage.hpp>
#include <ui/components/BaseComponent.hpp>
#include <ui/expressions/ExpressionCalculator.hpp>
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

		void setImageOffsets(const Expression &x, const Expression &y) override;
		void setImageSize(const Rect &sizeRect) override;
		void setImageRect(const Rect &srcRect, const Rect &dstRect) override;
		void setImageNinePath(const RectI &centerRect, const Rect &dstRect) override;

		void draw(SkCanvas *parentCanvas) override;
		void updateContext(const Context &ctx) override;
	private:
		std::shared_ptr<const ITexture> texture_;
		sk_sp<SkImage> image_;

		ImageMode mode_ = ImageMode::Default;
		Rect srcRect_;
		SkIRect centerRect_;
		Rect dstRect_;

		SkPaint paint_;
		SkCanvas::SrcRectConstraint srcRectConstraint_ = SkCanvas::SrcRectConstraint::kStrict_SrcRectConstraint;
		SkSamplingOptions samplingOptions_;
		SkFilterMode filterMode_ = SkFilterMode::kNearest;

		Context currentContext_ {};
		ExpressionCalculator calculator_;
	};
}