#include <ui/Image.hpp>
using namespace CubA4::render::ui;

Image::Image(std::shared_ptr<const ITexture> texture, sk_sp<SkImage> image) :
	texture_(texture), image_(image)
{

}

void Image::draw(SkCanvas *parentCanvas)
{
	parentCanvas->drawImage(image_, 10, 10);
}