#pragma once

#include <memory>

namespace CubA4::object
{
	class IEntity;
}


namespace CubA4::physics
{
	class IPhysicsEntityControllerWrapper;

	class IPhysicsEntityControl
	{
	public:
		virtual std::shared_ptr<IPhysicsEntityControllerWrapper> createController(const CubA4::object::IEntity &entity) = 0;
	protected:
		IPhysicsEntityControl() = default;
		virtual ~IPhysicsEntityControl() = default;
	};
}