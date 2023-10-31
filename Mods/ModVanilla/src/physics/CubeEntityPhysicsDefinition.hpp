#pragma once

#include <physics/IPhysicsEntityDefinition.hpp>

namespace CubA4::physics
{
	class CubeEntityPhysicsDefinition : public virtual IPhysicsEntityDefinition
	{
	public:
		CubeEntityPhysicsDefinition(std::shared_ptr<const ICollistionBodyDefinition> bodyDef);
		~CubeEntityPhysicsDefinition();

		bool includePhysicsController() const override;
		float getMass() const override;
		std::shared_ptr<const ICollistionBodyDefinition> getCollisonBody() const override;
	private:
		const std::shared_ptr<const ICollistionBodyDefinition> bodyDef_;
	};
}