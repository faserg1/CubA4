#pragma once

#include <memory>

namespace CubA4::physics
{
	class PhysicsEntityControllerWrapper;
};

namespace CubA4::object
{
	struct PhysicalControllerComponent
	{
		std::shared_ptr<CubA4::physics::PhysicsEntityControllerWrapper> wrapper;
	};
}