#pragma once

#include <physics/IPhysicsEntityDefinition.hpp>

namespace CubA4::physics
{
	class PlayerPhysicsDefinition : public virtual IPhysicsEntityDefinition
	{
	public:
		PlayerPhysicsDefinition(std::shared_ptr<const ICollistionBodyDefinition> bodyDef);
		~PlayerPhysicsDefinition();

		bool includePhysicsController() const override;
		float getMass() const override;
		std::shared_ptr<const ICollistionBodyDefinition> getCollisonBody() const override;
	private:
		const std::shared_ptr<const ICollistionBodyDefinition> bodyDef_;
	};
}