#pragma once

#include <core/IAppClientCallback.hpp>
#include <game/controller/IController.hpp>
#include <game/controller/Bindings.hpp>
#include <game/controller/RootActions.hpp>
#include <game/controller/Context.hpp>
#include <unordered_map>
#include <vector>

namespace CubA4::game::controller
{
	class Controller : public virtual IController
	{
		
	public:
		explicit Controller(CubA4::core::IAppClientCallback &appCallback);
		~Controller();

		void onButtonChanged(Button btn, BMods mods, bool pressed) override;
		void onPosition(int32_t x, int32_t y) override;
		void onMove(AxisBinding binding, int32_t x, int32_t y) override;
		
		std::pair<bool, BMods> getButtonState(Button btn) const override;
		bool getActionState(const std::string &action) const override;
		std::shared_ptr<const IRootActions> getRootActions() const override;
		std::shared_ptr<const IBindings> getBindings() const override;
		std::shared_ptr<IRootActions> getRootActions() override;
		std::shared_ptr<IBindings> getBindings() override;
		const IContext &getContext() const override;
		IContext &getContext() override;
		bool requestMouseCapture(bool enable) override;
	private:
		CubA4::core::IAppClientCallback &appCallback_;
		std::shared_ptr<RootActions> actions_;
		std::shared_ptr<Bindings> bindings_;
		std::unique_ptr<Context> context_;

		int32_t x_;
		int32_t y_;
	};
}
