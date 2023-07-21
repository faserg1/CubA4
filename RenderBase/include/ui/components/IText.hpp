#pragma once

#include <ui/components/IRenderUIBaseComponent.hpp>
#include <string>

namespace CubA4::render::ui
{
	class IText : public virtual IRenderUIBaseComponent
	{
	public:
		virtual void setText(const std::string &text) = 0;
		virtual void setTextOffset(float x, float y) = 0;
	protected:
		IText() = default;
		virtual ~IText() = default;
	};
}