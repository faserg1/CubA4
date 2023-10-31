#pragma once

#include <memory>
#include <base/Vector.hpp>

namespace CubA4::physics
{
	class IPhysicsEntityControllerWrapper
	{
	public:
		virtual ~IPhysicsEntityControllerWrapper() = default;

		virtual void setVelocity(const CubA4::Vector3 &velocity) = 0;
		virtual void applyImpulse(const CubA4::Vector3 &velocity, const CubA4::Vector3 &relativePosition) = 0;
	protected:
		IPhysicsEntityControllerWrapper() = default;
		
	};
}