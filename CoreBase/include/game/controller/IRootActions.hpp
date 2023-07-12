#pragma once

#include <memory>
#include <game/controller/IActions.hpp>
#include <game/controller/IContextActions.hpp>

namespace CubA4::game::controller
{
	class IRootActions : public virtual IActions
	{
	public:
		virtual ~IRootActions() = default;

		virtual std::shared_ptr<IContextActions> addContextActions(std::unique_ptr<IContextActionsRules> &&rules) = 0;
	protected:
		explicit IRootActions() = default;
	};
}
