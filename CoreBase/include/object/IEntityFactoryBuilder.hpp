#pragma once

#include <memory>

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

		void applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def);
	protected:
		explicit IEntityFactoryBuilder() = default;
	};
}
