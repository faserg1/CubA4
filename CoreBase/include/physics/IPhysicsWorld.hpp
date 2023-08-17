#pragma once

#include <world/GlobalPosition.hpp>

namespace CubA4::physics
{
	class IPhysicsWorld
	{
	public:
		virtual ~IPhysicsWorld() = default;

		virtual void rayTest(CubA4::world::GlobalPosition from, CubA4::world::GlobalPosition to) const = 0;
	protected:
		IPhysicsWorld() = default;
	};
}