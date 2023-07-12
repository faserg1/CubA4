#pragma once

#include <string>
#include <game/controller/Buttons.hpp>
#include <game/controller/IBindings.hpp>
#include <game/controller/IRootActions.hpp>
#include <game/controller/IContext.hpp>

namespace CubA4::game::controller
{
	class IController
	{
	public:
		virtual ~IController() = default;

		virtual void onButtonChanged(Button btn, BMods mods, bool pressed) = 0;
		virtual void onPosition(int32_t x, int32_t y) = 0;
		virtual void onMove(AxisBinding binding, int32_t x, int32_t y) = 0;
		virtual std::pair<bool, BMods> getButtonState(Button btn) const = 0;
		virtual bool getActionState(const std::string &action) const = 0;

		// TODO: Change shared_ptr to simple &

		virtual std::shared_ptr<const IRootActions> getRootActions() const = 0;
		virtual std::shared_ptr<const IBindings> getBindings() const = 0;
		virtual std::shared_ptr<IRootActions> getRootActions() = 0;
		virtual std::shared_ptr<IBindings> getBindings() = 0;
		virtual const IContext &getContext() const = 0;
		virtual IContext &getContext() = 0;
		virtual bool requestMouseCapture(bool enable) = 0;
	protected:
		explicit IController() = default;
	};
}
