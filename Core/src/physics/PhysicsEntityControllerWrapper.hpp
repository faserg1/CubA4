#pragma once

#include <physics/IPhysicsEntityControllerWrapper.hpp>
#include <entt/fwd.hpp>

namespace CubA4::physics
{

	// TODO: This should work as proxy?
	class PhysicsEntityControllerWrapper :
		public virtual IPhysicsEntityControllerWrapper,
		public std::enable_shared_from_this<PhysicsEntityControllerWrapper>
	{
	public:
		PhysicsEntityControllerWrapper(entt::registry &registry, entt::entity entity);

		void setVelocity(const CubA4::Vector3 &velocity) override;
		void applyImpulse(const CubA4::Vector3 &velocity, const CubA4::Vector3 &relativePosition) override;
	private:
		entt::registry &registry_;
		const entt::entity entity_;
	};
}