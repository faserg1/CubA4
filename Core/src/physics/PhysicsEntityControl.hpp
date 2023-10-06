#pragma once

#include <physics/IPhysicsEntityControl.hpp>

namespace CubA4::physics
{
	class PhysicsEntityControl : public virtual IPhysicsEntityControl
	{
	public:
		std::shared_ptr<IPhysicsEntityControllerWrapper> createController(const CubA4::object::IEntity &entity) override;
	};
}