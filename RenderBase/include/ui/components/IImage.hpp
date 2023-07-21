#pragma once

#include <ui/components/IRenderUIBaseComponent.hpp>

namespace CubA4::render::ui
{
	class IImage : public virtual IRenderUIBaseComponent
	{
	public:
	protected:
		IImage() = default;
		virtual ~IImage() = default;
	};
}