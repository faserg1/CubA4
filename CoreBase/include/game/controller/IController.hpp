#pragma once

#include <string>
#include <game/controller/Buttons.hpp>
#include <game/controller/IBindings.hpp>
#include <game/controller/IActions.hpp>

namespace CubA4::game::controller
{
	class IController
	{
	public:
		virtual ~IController() = default;

		virtual void onButtonChanged(Button btn, BMods mods, bool pressed) = 0;
		virtual std::pair<bool, BMods> getButtonState(Button btn) const = 0;
		virtual std::shared_ptr<const IActions> getActions() const = 0;
		virtual std::shared_ptr<const IBindings> getBindings() const = 0;
		virtual std::shared_ptr<IActions> getActions() = 0;
		virtual std::shared_ptr<IBindings> getBindings() = 0;
		virtual bool requestMouseCapture(bool enable) = 0;
	protected:
		explicit IController() = default;
	};
}
