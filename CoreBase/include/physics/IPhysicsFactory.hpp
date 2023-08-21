#pragma once

#include <memory>
#include <base/Vector.hpp>

namespace CubA4::physics
{
	class ICollistionBodyDefinition;
}


namespace CubA4::physics
{
	class IPhysicsFactory
	{
	public:
		virtual std::shared_ptr<CubA4::physics::ICollistionBodyDefinition> createBoxCollisionBody(const Vector3 &halfExtents, const Vector3 &offset) = 0;
	protected:
		IPhysicsFactory() = default;
		virtual ~IPhysicsFactory() = default;
	};
}