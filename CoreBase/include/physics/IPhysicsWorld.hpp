#pragma once

#include <world/GlobalPosition.hpp>
#include <world/RayTestResult.hpp>

namespace CubA4::physics
{
	class IPhysicsWorld
	{
	public:
		virtual ~IPhysicsWorld() = default;

		virtual CubA4::world::RayTestResult closestBlockRayTest(CubA4::world::GlobalPosition from, CubA4::world::GlobalPosition to) const = 0;
	protected:
		IPhysicsWorld() = default;
	};
}