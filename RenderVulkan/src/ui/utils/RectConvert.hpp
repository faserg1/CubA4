#pragma once

#include <ui/types/Rect.hpp>
#include <skia/include/core/SkRect.h>

namespace CubA4::render::ui
{
	constexpr SkRect toSkia(const Rect &rect)
	{
		return SkRect {
			.fLeft = rect.left,
			.fTop = rect.top,
			.fRight = rect.right,
			.fBottom = rect.bottom,
		};
	};

	constexpr SkIRect toSkia(const RectI &rect)
	{
		return SkIRect {
			.fLeft = rect.left,
			.fTop = rect.top,
			.fRight = rect.right,
			.fBottom = rect.bottom,
		};
	};
}