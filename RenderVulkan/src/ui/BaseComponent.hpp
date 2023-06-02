#pragma once

#include <ui/IRenderUIBaseComponent.hpp>
#include <skia/include/core/SkCanvas.h>

namespace CubA4::render::ui
{
	class BaseComponent : public virtual IRenderUIBaseComponent
	{
	public:
		void setVisibility(bool visibility) override {visibility_ = visibility; }
		bool isVisible() const override { return visibility_; }

		virtual void draw(SkCanvas *parentCanvas) {};
	private:
		bool visibility_ = true;
	};
}