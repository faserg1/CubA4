#pragma once

#include <memory>
#include <base/Vector.hpp>

namespace CubA4::physics
{
	class IPhysicsEntityDefinition;
}

namespace CubA4::object
{
	class IEntityFactoryBuilder
	{
	public:
		virtual ~IEntityFactoryBuilder() = default;

		virtual void applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def) = 0;
	protected:
		explicit IEntityFactoryBuilder() = default;
	};
}
