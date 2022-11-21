#include <game/controller/Actions.hpp>
using namespace CubA4::game::controller;

Actions::Actions()
{
	
}

Actions::~Actions()
{
	
}

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionCallback(const std::string &action, std::function<void()> callbackOnce)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackOnce = callbackOnce};
	addActionCallback(action, callback);
	return std::move(std::make_unique<Subscription>(shared_from_this(), action, id));
}

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackAxis = callbackAxis};
	addActionCallback(action, callback);
	return std::move(std::make_unique<Subscription>(shared_from_this(), action, id));
}

std::unique_ptr<CubA4::util::ISubscription> Actions::addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition)
{
	auto id = idCounter_++;
	auto callback = Callback{.id = id, .callbackAxis = callbackPosition};
	addActionCallback(action, callback);
	return std::move(std::make_unique<Subscription>(shared_from_this(), action, id));
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

Actions::Subscription::Subscription(std::shared_ptr<Actions> actions, const std::string &action, uint64_t id) :
	actions_(actions), action_(action), id_(id)
{

}

Actions::Subscription::~Subscription()
{
	unsubscribe();
}

void Actions::Subscription::unsubscribe()
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
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback();
}

void Actions::onAxisAction(const std::string &action, int32_t axisX, int32_t axisY)
{
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback(axisX, axisY);
}

void Actions::onPositionAction(const std::string &action, int32_t axisX, int32_t axisY)
{
	const auto actionIt = callbacks_.find(action);
	if (actionIt == callbacks_.end())
		return;
	for (auto &callback : actionIt->second)
		callback(axisX, axisY);
}