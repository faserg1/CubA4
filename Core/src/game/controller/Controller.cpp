#include <game/controller/Controller.hpp>
#include <algorithm>
using namespace CubA4::game::controller;

Controller::Controller(CubA4::system::IAppCallback &appCallback) :
	appCallback_(appCallback), actions_(std::make_shared<Actions>()), bindings_(std::make_shared<Bindings>())
{
	
}

Controller::~Controller()
{
	
}

void Controller::onButtonChanged(Button btn, BMods mods, bool pressed)
{
	if (!pressed)
		return;
	auto state = appCallback_.getButtonState(btn);
	auto actions = bindings_->getKeyAction(btn, state.second);
	if (!actions)
		return;
	for (const auto &action : *actions)
	{
		actions_->onAction(action);
		actions_->onPositionAction(action, x_, y_);
	}
}

void Controller::onPosition(int32_t x, int32_t y)
{
	x_ = x;
	y_ = y;
	// TODO:  ?
}

void Controller::onMove(AxisBinding binding, int32_t x, int32_t y)
{
	auto actions = bindings_->getAxisAction(binding);
	if (!actions)
		return;
	for (const auto &action : *actions)
		actions_->onAxisAction(action, x, y);
}

std::pair<bool, BMods> Controller::getButtonState(Button btn) const
{
	return appCallback_.getButtonState(btn);
}

bool Controller::getActionState(const std::string &action) const
{
	return bindings_->forEachKeyAction(action, [this](auto btn, auto bmods) -> bool
	{
		return getButtonState(btn).first;
	});
}

std::shared_ptr<const IActions> Controller::getActions() const
{
	return actions_;
}

std::shared_ptr<const IBindings> Controller::getBindings() const
{
	return bindings_;
}

std::shared_ptr<IActions> Controller::getActions()
{
	return actions_;
}

std::shared_ptr<IBindings> Controller::getBindings()
{
	return bindings_;
}

bool Controller::requestMouseCapture(bool enable)
{
	return appCallback_.requestMouseCapture(enable);
}