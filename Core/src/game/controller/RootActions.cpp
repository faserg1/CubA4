#include <game/controller/RootActions.hpp>
#include <game/controller/ContextActions.hpp>
using namespace CubA4::game::controller;


RootActions::RootActions() = default;
RootActions::~RootActions() = default;

std::shared_ptr<IContextActions> RootActions::addContextActions(std::unique_ptr<IContextActionsRules> &&rules)
{
	return std::make_shared<ContextActions>(std::move(rules), shared_from_this());
}