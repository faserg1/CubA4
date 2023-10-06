#pragma once

#include <memory>
#include <game/controller/ContextActionsWithArgs.hpp>

namespace CubA4::object
{
	class IEntity;
	using EntityArg = std::weak_ptr<IEntity>;
	using EntityContextActions = CubA4::game::controller::ContextActionsWithArgs<EntityArg>;
	using IEntityContextActions = CubA4::game::controller::IActionsHandlerArgs<EntityArg>;
}