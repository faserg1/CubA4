#include <ui/MainCanvas.hpp>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkFont.h>
using namespace CubA4::render::ui;

void MainCanvas::draw(SkCanvas *parentCanvas)
{
	Frame::draw(parentCanvas);
	SkPoint center = {200, 200};
	SkScalar rad = 100;
	
	SkColor4f color = {0, 0, 0, 1};
	SkPaint paint(color);
	paint.setAntiAlias(true);
	parentCanvas->drawCircle(center, rad, paint);

	std::string text("UI is here!");
	SkFont font;
	font.setSize(32);
	parentCanvas->drawSimpleText(text.data(), text.size(), SkTextEncoding::kUTF8, 100, 400, font, paint);
}