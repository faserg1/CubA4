#include <engine/material/TextureHelper.hpp>
#include <cmath>
using namespace CubA4::render::engine::material;

double CubA4::render::engine::material::SRGBtoLinear(uint8_t color)
{
	if (color <= 0.04045)
		return static_cast<double>(color) / 12.92;
	return std::pow((static_cast<double>(color) + 0.055) / 1.055, 2.4);
}

uint8_t CubA4::render::engine::material::LineartoSRGB(double color)
{
	if (color <= 0.0031308)
		return static_cast<uint8_t>(color * 12.92);
	return static_cast<uint8_t>(1.055 * std::pow(color, 1 / 2.4) - 0.055);
}

uint8_t CubA4::render::engine::material::blendNoAlpha(std::initializer_list<uint8_t> toBlend)
{
	double total = 0;
	for (auto color : toBlend)
		total += SRGBtoLinear(color);
	return LineartoSRGB(total / toBlend.size());
}

uint8_t CubA4::render::engine::material::blendLinear(std::initializer_list<uint8_t> toBlend)
{
	uint16_t total = 0;
	for (auto color : toBlend)
		total += color;
	return static_cast<uint8_t>(total / toBlend.size());
}