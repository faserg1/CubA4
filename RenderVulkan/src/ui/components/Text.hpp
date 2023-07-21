#pragma once

#include <memory>
#include <string>
#include <ui/components/IText.hpp>
#include <ui/components/BaseComponent.hpp>
#include <skia/include/core/SkFont.h>

namespace CubA4::render::ui
{
	class Text : public BaseComponent, public virtual IText
	{
	public:
		Text();
		void setTextOffset(float x, float y) override;
		void setText(const std::string &text) override;
		void draw(SkCanvas *parentCanvas) override;
	private:
		std::string text_;
		SkFont font_;
		float offsetX_ = 0;
		float offsetY_ = 0;
	};
}