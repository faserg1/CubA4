#pragma once

#include <game/controller/IContextActions.hpp>
#include <game/controller/IContext.hpp>
#include <game/controller/IActions.hpp>
#include <memory>
#include <vector>

namespace CubA4::game::controller
{
	class ContextActions : public virtual IContextActions
	{
	public:
		ContextActions(std::unique_ptr<IContextActionsRules> &&rules, std::shared_ptr<IActions> actions);
		void addActionCallback(const std::string &action, std::function<void()> callbackOnce) override;
		void addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		void addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		void addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;

		void onContextChanged(const IContext &context);
	private:
		std::unique_ptr<IContextActionsRules> rules_;
		std::weak_ptr<IActions> actions_;
		std::vector<std::unique_ptr<util::ISubscription>> subscriptions_;
		bool enabled_ = false;
	};
}