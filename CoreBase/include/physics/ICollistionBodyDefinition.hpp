#pragma once

#include <cstdint>
#include <base/Vector.hpp>

namespace CubA4::physics
{
	enum class BodyType : int8_t
	{
		Box = 0,
	};

	class ICollistionBodyDefinition
	{
	public:
		virtual BodyType getType() const = 0;
		virtual Vector3 getOffset() const = 0;
	protected:
		ICollistionBodyDefinition() = default;
		virtual ~ICollistionBodyDefinition() = default;
	};
}