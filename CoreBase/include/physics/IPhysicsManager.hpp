#pragma once

#include <memory>
#include <physics/IPhysicsWorld.hpp>
#include <physics/IWorldPhysicsDefinition.hpp>
#include <object/IEntity.hpp>

namespace CubA4::physics
{
	class ICollistionBodyDefinition;
	class IPhysicsFactory;
}


namespace CubA4::physics
{
	class IPhysicsManager
	{
	public:
		// TODO: co_async?
		virtual void requestApplyForce(CubA4::object::IEntity &entity) = 0;
		virtual IPhysicsFactory &getPhysicsFactory() const = 0;
	protected:
		IPhysicsManager() = default;
		virtual ~IPhysicsManager() = default;
	};
}