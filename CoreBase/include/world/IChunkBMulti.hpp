#pragma once

#include <world/IChunkBBaseContainer.hpp>

namespace CubA4::world
{
	class IChunkBMulti : public IChunkBBaseContainer
	{
	public:
		virtual ~IChunkBMulti() = default;
		ChunkBContainerType getType() const override final { return ChunkBContainerType::Multi; }
	protected:
		explicit IChunkBMulti() = default;
	};
}
