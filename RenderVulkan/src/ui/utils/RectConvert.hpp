#pragma once

#include <ui/types/Rect.hpp>
#include <skia/include/core/SkRect.h>

namespace CubA4::render::ui
{
	constexpr SkIRect toSkia(const RectI &rect)
	{
		return SkIRect {
			.fLeft = rect.left,
			.fTop = rect.top,
			.fRight = rect.right,
			.fBottom = rect.bottom,
		};
	};

	constexpr SkRect toSkia(const RectF &rect)
	{
		return SkRect {
			.fLeft = rect.left,
			.fTop = rect.top,
			.fRight = rect.right,
			.fBottom = rect.bottom,
		};
	};

	constexpr SkRect toSkia(const RectLD &rect)
	{
		return SkRect {
			.fLeft = static_cast<float>(rect.left),
			.fTop = static_cast<float>(rect.top),
			.fRight = static_cast<float>(rect.right),
			.fBottom = static_cast<float>(rect.bottom),
		};
	};
}