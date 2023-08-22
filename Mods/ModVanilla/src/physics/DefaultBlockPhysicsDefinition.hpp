#pragma once

#include <physics/IBlockPhysicsDefinition.hpp>

namespace CubA4::physics
{
	class DefaultBlockPhysicsDefinition :
		public virtual IBlockPhysicsDefinition
	{
	public:
		BlockShape getShape(const CubA4::world::BlockData &data) const override;
	};
}