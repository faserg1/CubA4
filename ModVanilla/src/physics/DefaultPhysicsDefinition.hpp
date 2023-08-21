#pragma once

#include <physics/IWorldPhysicsDefinition.hpp>

namespace CubA4::physics
{
	class DefaultPhysicsDefinition : public virtual IWorldPhysicsDefinition
	{
	public:
		Vector3 getDefaultGravity() const override;
	};
}