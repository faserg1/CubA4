#pragma once

#include <system/IAppCallback.hpp>
#include <game/controller/IController.hpp>
#include <game/controller/Bindings.hpp>
#include <game/controller/Actions.hpp>
#include <unordered_map>
#include <vector>

namespace CubA4::game::controller
{
	class Controller : public virtual IController
	{
		
	public:
		explicit Controller(CubA4::system::IAppCallback &appCallback);
		~Controller();

		void onButtonChanged(Button btn, BMods mods, bool pressed) override;
		std::pair<bool, BMods> getButtonState(Button btn) const override;
		std::shared_ptr<const IActions> getActions() const override;
		std::shared_ptr<const IBindings> getBindings() const override;
		std::shared_ptr<IActions> getActions() override;
		std::shared_ptr<IBindings> getBindings() override;
		bool requestMouseCapture(bool enable) override;
	private:
		CubA4::system::IAppCallback &appCallback_;
		std::shared_ptr<Actions> actions_;
		std::shared_ptr<Bindings> bindings_;
	};
}
