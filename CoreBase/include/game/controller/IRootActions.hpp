#pragma once

#include <memory>
#include <game/controller/IActions.hpp>
#include <game/controller/IContextActions.hpp>

namespace CubA4::game::controller
{
	template <class ...Args>
	class ContextActionsWithArgs;

	class IRootActions : public virtual IActions
	{
	public:
		virtual ~IRootActions() = default;

		virtual std::shared_ptr<IContextActions> addContextActions(std::unique_ptr<IContextActionsRules> &&rules) = 0;
		template <class ...Args>
		std::shared_ptr<ContextActionsWithArgs<Args...>> addContextActions(std::unique_ptr<IContextActionsRules> &&rules, std::tuple<Args...> args)
		{
			return std::make_shared<ContextActionsWithArgs<Args...>>(addContextActions(std::move(rules)), args);
		}
	protected:
		explicit IRootActions() = default;
	};
}
