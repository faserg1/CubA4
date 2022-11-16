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
		actions_->onAction(action);
}

std::pair<bool, BMods> Controller::getButtonState(Button btn) const
{
	return appCallback_.getButtonState(btn);
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