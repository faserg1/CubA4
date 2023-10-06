#include <object/EntityControllerRules.hpp>
#include <object/IEntity.hpp>
using namespace CubA4::object;

EntityControllerRules::EntityControllerRules(std::shared_ptr<const IEntity> entity, std::shared_ptr<CubA4::game::controller::IContextActionsRules> childRules) :
	entity_(entity), childRules_(childRules)
{

}

bool EntityControllerRules::checkContext(const CubA4::game::controller::IContext &context) const
{
	auto entity = entity_.lock();
	if (!entity)
		return false;
	return entity->isControlsEnabled() && (childRules_ ? childRules_->checkContext(context) : true);
}