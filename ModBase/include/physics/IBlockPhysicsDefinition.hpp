#pragma once

#include <cstdint>
#include <memory>
#include <limits>
#include <world/data/BlockData.hpp>

namespace CubA4::physics
{
	enum class BlockShape : uint16_t
	{
		Box = 0,
		Custom = std::numeric_limits<uint16_t>::max(),
	};

	class IBlockPhysicsDefinition
	{
	public:
		virtual BlockShape getShape(const CubA4::world::BlockData &data) const = 0;
	protected:
		IBlockPhysicsDefinition() = default;
	};
}