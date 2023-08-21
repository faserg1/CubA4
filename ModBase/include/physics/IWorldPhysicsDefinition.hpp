#pragma once

#include <base/Vector.hpp>

namespace CubA4::physics
{
	class IWorldPhysicsDefinition
	{
	public:
		virtual Vector3 getDefaultGravity() const = 0;
	protected:
		IWorldPhysicsDefinition() = default;
	};
}