#pragma once

#include <world/IChunk.hpp>
#include <type_traits>

namespace CubA4
{
	namespace core
	{
		namespace util
		{
			template <class TKey>
			class ChunkPosHashT
			{
				static_assert(std::is_same<TKey, CubA4::core::world::ChunkPos>::value, "TKey must be ChunkPos");
			public:
				size_t operator()(const CubA4::core::world::ChunkPos &chunkPos) const
				{
					constexpr auto axisHashSize = (sizeof(size_t) * 8) /4;
					size_t xKey = chunkPos.x % axisHashSize;
					size_t yKey = chunkPos.y % axisHashSize;
					size_t zKey = chunkPos.z % axisHashSize;
					return zKey << axisHashSize * 2 | yKey << axisHashSize | xKey;
				}
			};

			using ChunkPosHash = ChunkPosHashT<CubA4::core::world::ChunkPos>;
		}
	}
}

