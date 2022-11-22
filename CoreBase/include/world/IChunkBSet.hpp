#pragma once

#include <world/IChunkBUnion.hpp>

namespace CubA4::world
{
	class IChunkBSet : public IChunkBUnion
	{
	public:
		virtual ~IChunkBSet() = default;
	protected:
		explicit IChunkBSet() = default;
	};
}
