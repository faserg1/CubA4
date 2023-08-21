#pragma once

#include <physics/IPhysicsFactory.hpp>

namespace CubA4::physics
{
	class PhysicsFactory : public virtual IPhysicsFactory
	{
	public:
		PhysicsFactory();
		~PhysicsFactory();
		std::shared_ptr<CubA4::physics::ICollistionBodyDefinition> createBoxCollisionBody(const Vector3 &halfExtents, const Vector3 &offset) override;
	private:
	};
}