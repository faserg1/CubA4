#pragma once

#include <ui/expressions/Expression.hpp>

namespace CubA4::render::ui
{
	struct Rect
	{
		Expression left;
		Expression top;
		Expression right;
		Expression bottom;
	};

	struct RectF
	{
		float left = 0;
		float top = 0;
		float right = 0;
		float bottom = 0;
	};

	struct RectLD
	{
		long double left = 0;
		long double top = 0;
		long double right = 0;
		long double bottom = 0;
	};

	struct RectI
	{
		int32_t left = 0;
		int32_t top = 0;
		int32_t right = 0;
		int32_t bottom = 0;
	};
}
