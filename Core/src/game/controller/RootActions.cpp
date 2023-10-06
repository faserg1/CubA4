#include <game/controller/RootActions.hpp>
#include <game/controller/ContextActions.hpp>
#include <algorithm>
using namespace CubA4::game::controller;


RootActions::RootActions(IController *controller) :
	Actions(controller)
{

}

RootActions::~RootActions() = default;

std::shared_ptr<IContextActions> RootActions::addContextActions(std::unique_ptr<IContextActionsRules> &&rules)
{
	auto actions = std::make_shared<ContextActions>(std::move(rules), shared_from_this());
	addHandler(actions);
	contextActions_.push_back(actions);
	return actions;
}

void RootActions::onContextChanged(const IContext &context)
{
	std::vector<decltype(contextActions_)::iterator> toRemove;
	for (auto it = contextActions_.begin(); it != contextActions_.end(); it++)
	{
		if (it->expired())
		{
			toRemove.push_back(it);
			continue;
		}
		if (auto actions = it->lock())
		{
			actions->onContextChanged(context);
		}
	}
}