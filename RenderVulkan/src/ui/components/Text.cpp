#include <ui/components/Text.hpp>

using namespace CubA4::render::ui;

Text::Text()
{
	font_.setSize(32);
}

void Text::setText(const std::string &text)
{
	text_ = text;
}

void Text::setTextOffset(float x, float y)
{
	offsetX_ = x;
	offsetY_ = y;
}

void Text::draw(SkCanvas *parentCanvas)
{
	SkColor4f color = {1, 1, 1, 1};
	SkPaint paint(color);
	paint.setAntiAlias(true);
	
	parentCanvas->drawSimpleText(text_.data(), text_.size(), SkTextEncoding::kUTF8, offsetX_, offsetY_, font_, paint);
}