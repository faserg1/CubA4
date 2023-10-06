#pragma once

#include <physics/IPhysicsEntityControllerWrapper.hpp>
#include <entt/fwd.hpp>

namespace CubA4::physics
{

	// TODO: This should work as proxy?
	class PhysicsEntityControllerWrapper : public virtual IPhysicsEntityControllerWrapper
	{
	public:
		PhysicsEntityControllerWrapper(entt::registry &registry, entt::entity entity);

		void addVelocity(const CubA4::Vector3 &velocity) override;
	private:
		entt::registry &registry_;
		const entt::entity entity_;
	};
}