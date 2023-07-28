#pragma once

#include <ui/components/IRenderUIBaseComponent.hpp>
#include <ui/types/Rect.hpp>
#include <ui/types/ImageMode.hpp>

namespace CubA4::render::ui
{
	class IImage : public virtual IRenderUIBaseComponent
	{
	public:
		virtual void setMode(ImageMode mode) = 0;
		virtual ImageMode getMode() const = 0;

		virtual void setImageOffsets(float x, float y) = 0;
		virtual void setImageSize(const Rect &sizeRect) = 0;
		virtual void setImageRect(const Rect &srcRect, const Rect &dstRect) = 0;
		virtual void setImageNinePath(const RectI &centerRect, const Rect &dstRect) = 0;
	protected:
		IImage() = default;
		virtual ~IImage() = default;
	};
}