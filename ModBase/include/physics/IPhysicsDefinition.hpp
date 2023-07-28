#pragma once

#include <base/Vector.hpp>

namespace CubA4::physics
{
	class IPhysicsDefinition
	{
	public:
		virtual Vector3 getDefaultGravity() const = 0;
	protected:
		IPhysicsDefinition() = default;
	};
}