#pragma once

#include <world/IChunkBUnion.hpp>

namespace CubA4::world
{
	class IChunkBSet : public IChunkBUnion
	{
	public:
		virtual ~IChunkBSet() = default;
		ChunkBContainerType getType() const override final { return ChunkBContainerType::Set; }
	protected:
		explicit IChunkBSet() = default;
	};
}
