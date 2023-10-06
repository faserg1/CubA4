#pragma once

#include <memory>
#include <base/Vector.hpp>

namespace CubA4::physics
{
	class IPhysicsEntityControllerWrapper
	{
	public:
		virtual ~IPhysicsEntityControllerWrapper() = default;

		virtual void addVelocity(const CubA4::Vector3 &velocity) = 0;
	protected:
		IPhysicsEntityControllerWrapper() = default;
		
	};
}