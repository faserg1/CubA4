#pragma once

namespace CubA4::physics
{
	class IPhysicsWorld
	{
	public:
		virtual ~IPhysicsWorld() = default;
	protected:
		IPhysicsWorld() = default;
	};
}