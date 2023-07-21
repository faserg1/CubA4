#pragma once

#include <ui/components/IMainCanvas.hpp>
#include <ui/components/Frame.hpp>
#include <skia/include/core/SkCanvas.h>

namespace CubA4::render::ui
{
	class MainCanvas : public Frame, public virtual IMainCanvas
	{
	public:
		void draw(SkCanvas *parentCanvas) override;
	private:

	};
}