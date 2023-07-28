#pragma once

#include <physics/IPhysicsDefinition.hpp>

namespace CubA4::physics
{
	class DefaultPhysicsDefinition : public virtual IPhysicsDefinition
	{
	public:
		Vector3 getDefaultGravity() const override;
	};
}