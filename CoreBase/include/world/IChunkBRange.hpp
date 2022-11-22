#pragma once

#include <world/IChunkBUnion.hpp>

namespace CubA4::world
{
	class IChunkBRange : public IChunkBUnion
	{
	public:
		virtual ~IChunkBRange() = default;
	protected:
		explicit IChunkBRange() = default;
	};
}
