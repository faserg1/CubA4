#pragma once

#include <memory>
#include <object/EntityControllerTypes.hpp>

namespace CubA4::object
{
	struct ControllerComponent
	{
		const std::shared_ptr<EntityContextActions> actions;
	};
}
