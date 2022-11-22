#pragma once

#include <world/IChunkBBaseContainer.hpp>

namespace CubA4::world
{
	class IChunkBMulti : public IChunkBBaseContainer
	{
	public:
		ChunkBContainerType getType() const override final { return ChunkBContainerType::Multi; }
		virtual ~IChunkBMulti() = default;
	protected:
		explicit IChunkBMulti() = default;
	};
}
