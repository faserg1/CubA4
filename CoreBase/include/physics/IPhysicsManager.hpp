#pragma once

#include <physics/IPhysicsWorld.hpp>
#include <physics/IPhysicsDefinition.hpp>
#include <object/IEntity.hpp>

namespace CubA4::physics
{
	class IPhysicsManager
	{
	public:
		// TODO: co_async?
		virtual void requestApplyForce(CubA4::object::IEntity &entity) = 0;
	protected:
		IPhysicsManager() = default;
		virtual ~IPhysicsManager() = default;
	};
}