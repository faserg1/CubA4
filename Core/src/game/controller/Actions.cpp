#include <game/controller/Actions.hpp>
#include <game/controller/IController.hpp>
using namespace CubA4::game::controller;

Actions::Actions(IController *controller) :
	controller_(controller)
{
	
}

Actions::~Actions() = default;

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionCallback(const std::string &action, std::function<void()> callbackOnce)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackOnce = callbackOnce};
	addActionCallback(action, callback);
	return std::move(std::make_unique<SubscriptionSingle>(shared_from_this(), action, id));
}

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackAxis = callbackAxis};
	addActionCallback(action, callback);
	return std::move(std::make_unique<SubscriptionSingle>(shared_from_this(), action, id));
}

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackAxis = callbackPosition};
	addActionCallback(action, callback);
	return std::move(std::make_unique<SubscriptionSingle>(shared_from_this(), action, id));
}

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackAxis = callbackPosition};
	addActionCallback(action, callback);
	return std::move(std::make_unique<SubscriptionSingle>(shared_from_this(), action, id));
}

void Actions::addHandler(std::weak_ptr<IActionsHandler> handler)
{
	const auto id = idCounter_++;
	actionHandlers_.insert(std::make_pair(id, handler));
}

bool Actions::getActionState(const std::string &action) const
{
	return controller_->getActionState(action);
}

void Actions::requestContextCheck()
{
	controller_->getContext().forceUpdate();
}

void Actions::addActionCallback(const std::string &action, Callback callback)
{
	auto it = callbacks_.find(action);
	if (it == callbacks_.end())
		callbacks_.insert(std::make_pair(action, std::vector{callback}));
	else
	{
		it->second.push_back(callback);
	}
}

const std::unordered_map<std::string, std::vector<Actions::Callback>> &Actions::getCallbacks() const
{
	return callbacks_;
}

Actions::SubscriptionSingle::SubscriptionSingle(std::weak_ptr<Actions> actions, const std::string &action, uint64_t id) :
	actions_(actions), action_(action), id_(id)
{

}

Actions::SubscriptionSingle::~SubscriptionSingle()
{
	unsubscribe();
}

void Actions::SubscriptionSingle::unsubscribe()
{
	const auto lock = actions_.lock();
	if (!lock)
		return;
	const auto actionIt = lock->callbacks_.find(action_);
	if (actionIt == lock->callbacks_.end())
		return;
	auto it = std::find_if(actionIt->second.begin(), actionIt->second.end(), [id = this->id_](Actions::Callback &c)
	{
		return c.id == id;
	});
	if (it == actionIt->second.end())
		return;
	actionIt->second.erase(it);
}

void Actions::onAction(const std::string &action)
{
	for (auto [id, handlerWeak] : actionHandlers_)
	{
		auto handler = handlerWeak.lock();
		if (!handler)
			continue;
		handler->onAction(action);
	}
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback();
}

void Actions::onActionAxis(const std::string &action, int32_t axisX, int32_t axisY)
{
	for (auto [id, handlerWeak] : actionHandlers_)
	{
		auto handler = handlerWeak.lock();
		if (!handler)
			continue;
		handler->onActionAxis(action, axisX, axisY);
	}
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback(axisX, axisY);
}

void Actions::onActionPosition(const std::string &action, int32_t x, int32_t y)
{
	for (auto [id, handlerWeak] : actionHandlers_)
	{
		auto handler = handlerWeak.lock();
		if (!handler)
			continue;
		handler->onActionPosition(action, x, y);
	}
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback(x, y);
}

void Actions::onActionPositionMove(const std::string &action, int32_t x, int32_t y)
{
	for (auto [id, handlerWeak] : actionHandlers_)
	{
		auto handler = handlerWeak.lock();
		if (!handler)
			continue;
		handler->onActionPositionMove(action, x, y);
	}
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback(x, y);
}