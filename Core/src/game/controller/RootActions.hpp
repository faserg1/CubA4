#pragma once

#include <game/controller/IRootActions.hpp>
#include <game/controller/Actions.hpp>
#include <memory>

namespace CubA4::game::controller
{
	class RootActions : public Actions, public virtual IRootActions
	{
	public:
		explicit RootActions();
		~RootActions();

		std::shared_ptr<IContextActions> addContextActions(std::unique_ptr<IContextActionsRules> &&rules) override;
	};
}