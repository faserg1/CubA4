#pragma once

#include <world/IChunkBBaseContainer.hpp>

namespace CubA4::world
{
	class IChunkBUnion : public IChunkBBaseContainer
	{
	public:
		virtual ~IChunkBUnion() = default;
	protected:
		explicit IChunkBUnion() = default;
	};
}
