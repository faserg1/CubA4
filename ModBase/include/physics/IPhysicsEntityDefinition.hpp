#pragma once

#include <memory>

namespace CubA4::physics
{
	class ICollistionBodyDefinition;

	class IPhysicsEntityDefinition
	{
	public:
		virtual ~IPhysicsEntityDefinition() = default;

		virtual bool includePhysicsController() const = 0;
		virtual float getMass() const = 0;
		virtual std::shared_ptr<const ICollistionBodyDefinition> getCollisonBody() const = 0;
	protected:
		IPhysicsEntityDefinition() = default;
	};
}