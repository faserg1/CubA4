#include <game/controller/ContextActions.hpp>
using namespace CubA4::game::controller;

ContextActions::ContextActions(std::unique_ptr<IContextActionsRules> &&rules, std::shared_ptr<IActions> actions) :
	rules_(std::move(rules)), actions_(actions)
{

}

void ContextActions::addActionCallback(const std::string &action, std::function<void()> callbackOnce)
{
	if (auto actions = actions_.lock())
	{
		subscriptions_.emplace_back(std::move(
			actions->addActionCallback(action, [enabled = &enabled_, callbackOnce]()
			{
				if (!enabled)
					return;
				callbackOnce();
			})
		));
	}
}

void ContextActions::addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis)
{
	if (auto actions = actions_.lock())
	{
		subscriptions_.emplace_back(std::move(
			actions->addActionAxisCallback(action, [enabled = &enabled_, callbackAxis](int32_t x, int32_t y)
			{
				if (!enabled)
					return;
				callbackAxis(x, y);
			})
		));
	}
}

void ContextActions::addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis)
{
	if (auto actions = actions_.lock())
	{
		subscriptions_.emplace_back(std::move(
			actions->addActionPositionCallback(action, [enabled = &enabled_, callbackAxis](int32_t x, int32_t y)
			{
				if (!enabled)
					return;
				callbackAxis(x, y);
			})
		));
	}
}

void ContextActions::addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis)
{
	if (auto actions = actions_.lock())
	{
		subscriptions_.emplace_back(std::move(
			actions->addActionPositionMoveCallback(action, [enabled = &enabled_, callbackAxis](int32_t x, int32_t y)
			{
				if (!enabled)
					return;
				callbackAxis(x, y);
			})
		));
	}
}

void ContextActions::onContextChanged(const IContext &context)
{
	enabled_ = rules_->checkContext(context);
}