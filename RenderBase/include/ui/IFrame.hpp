#pragma once

#include <memory>
#include <ui/IRenderUIBaseComponent.hpp>

namespace CubA4::render::ui
{
	class IFrame : public virtual IRenderUIBaseComponent
	{
	public:
		// TODO: add remove etc
		virtual void addComponent(std::shared_ptr<IRenderUIBaseComponent> component) = 0;
	};
}