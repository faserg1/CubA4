#pragma once

#include <memory>

namespace CubA4::render::engine::material
{
	double SRGBtoLinear(uint8_t color);
	uint8_t LineartoSRGB(double color);

	uint8_t blendNoAlpha(std::initializer_list<uint8_t> toBlend);
}