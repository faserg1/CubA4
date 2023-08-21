#pragma once

#include <base/Vector.hpp>
#include <physics/ICollistionBodyDefinition.hpp>

namespace CubA4::physics
{
	class BoxCollisionBodyDefinition : public virtual ICollistionBodyDefinition
	{
	public:
		BoxCollisionBodyDefinition(Vector3 halfExtents, Vector3 offset);

		BodyType getType() const override;

		Vector3 getHalfExtents() const;
		Vector3 getOffset() const override;
	private:
		const Vector3 halfExtents_;
		const Vector3 offset_;
	};
}