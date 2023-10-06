#pragma once

#include <game/controller/IRootActions.hpp>
#include <game/controller/Actions.hpp>
#include <memory>

namespace CubA4::game::controller
{
	class ContextActions;

	class RootActions : public Actions, public virtual IRootActions
	{
	public:
		explicit RootActions(IController *controller);
		~RootActions();

		std::shared_ptr<IContextActions> addContextActions(std::unique_ptr<IContextActionsRules> &&rules) override;
		void onContextChanged(const IContext &context);
	private:
		std::vector<std::weak_ptr<ContextActions>> contextActions_;
	};
}