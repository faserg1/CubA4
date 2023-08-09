#pragma once

#include <memory>
#include <bullet/btBulletDynamicsCommon.h>
#include <entt/entt.hpp>

namespace CubA4::object
{
	class MotionState;

	struct PhysicalBody
	{
		std::unique_ptr<btRigidBody> collisionObject;
		std::unique_ptr<btCollisionShape> shape;
		std::unique_ptr<btCompoundShape> offsetShape;
		std::unique_ptr<MotionState> motionState;
	};

	class MotionState : public btMotionState
	{
	public:
		MotionState(entt::registry &registry, entt::entity entity);

		void getWorldTransform(btTransform& worldTrans) const;
		void setWorldTransform(const btTransform& worldTrans);
	private:
		entt::registry &registry_;
		const entt::entity entity_;
	};
}
