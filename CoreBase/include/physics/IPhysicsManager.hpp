#pragma once

#include <physics/IPhysicsWorld.hpp>
#include <physics/IPhysicsDefinition.hpp>

namespace CubA4::physics
{
	class IPhysicsManager
	{
	public:
		virtual std::unique_ptr<IPhysicsWorld> addPhysicsWorld(const IPhysicsDefinition &definition) = 0;
	protected:
		IPhysicsManager() = default;
		virtual ~IPhysicsManager() = default;
	};
}