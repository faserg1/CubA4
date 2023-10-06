#include <game/controller/ContextActions.hpp>
using namespace CubA4::game::controller;

ContextActions::ContextActions(std::unique_ptr<IContextActionsRules> &&rules, std::shared_ptr<IActions> actions) :
	rules_(std::move(rules)), actions_(actions)
{
}

void ContextActions::addActionCallback(const std::string &action, std::function<void()> callbackOnce)
{
	getCallback(action, true)->once.push_back(callbackOnce);
}

void ContextActions::addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis)
{
	getCallback(action, true)->axis.push_back(callbackAxis);
}

void ContextActions::addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition)
{
	getCallback(action, true)->position.push_back(callbackPosition);
}

void ContextActions::addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPositionMove)
{
	getCallback(action, true)->positionMove.push_back(callbackPositionMove);
}

void ContextActions::onContextChanged(const IContext &context)
{
	enabled_ = rules_ ? rules_->checkContext(context) : true;
}

void ContextActions::addHandler(std::shared_ptr<IActionsHandler> handler)
{
	actionHandlers_.push_back(handler);
}

bool ContextActions::getActionState(const std::string &action) const
{
	return enabled_ && !actions_.expired() && actions_.lock()->getActionState(action);
}

void ContextActions::requestContextCheck()
{
	if (auto actions = actions_.lock())
		actions->requestContextCheck();
}

void ContextActions::onAction(const std::string &action)
{
	if (!enabled_)
		return;
	if (auto callbacks = getCallback(action))
	{
		for (auto callback : callbacks->once)
			callback();
	}
	for (auto actionHandler : actionHandlers_)
		actionHandler->onAction(action);
}

void ContextActions::onActionAxis(const std::string &action, int32_t x, int32_t y)
{
	if (!enabled_)
		return;
	if (auto callbacks = getCallback(action))
	{
		for (auto callback : callbacks->axis)
			callback(x, y);
	}
	for (auto actionHandler : actionHandlers_)
		actionHandler->onActionAxis(action, x, y);
}

void ContextActions::onActionPosition(const std::string &action, int32_t x, int32_t y)
{
	if (!enabled_)
		return;
	if (auto callbacks = getCallback(action))
	{
		for (auto callback : callbacks->position)
			callback(x, y);
	}
	for (auto actionHandler : actionHandlers_)
		actionHandler->onActionPosition(action, x, y);
}

void ContextActions::onActionPositionMove(const std::string &action, int32_t x, int32_t y)
{
	if (!enabled_)
		return;
	if (auto callbacks = getCallback(action))
	{
		for (auto callback : callbacks->positionMove)
			callback(x, y);
	}
	for (auto actionHandler : actionHandlers_)
		actionHandler->onActionPositionMove(action, x, y);
}

ContextActions::Callbacks *ContextActions::getCallback(const std::string &action, bool addIfNotExists)
{
	Callbacks *callbacks = nullptr;
	auto it = callbacks_.find(action);
	if (it != callbacks_.end())
		callbacks = &it->second;
	else if (addIfNotExists)
	{
		auto [it, added] = callbacks_.insert(std::pair(action, Callbacks{}));
		callbacks = &it->second;
	}
	return callbacks;
}