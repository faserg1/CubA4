#pragma once

#include <memory>
#include <vector>
#include <entt/signal/sigh.hpp>

namespace CubA4::object
{
	class Entity;

	struct InternalEntityInfo
	{
		std::weak_ptr<Entity> entity;
	};
}