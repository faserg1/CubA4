#ifndef CHUNKPOSHASH_HPP
#define CHUNKPOSHASH_HPP

#include <world\IChunk.hpp>
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
				static_assert(std::is_same_v<TKey, CubA4::mod::world::ChunkPos>, "TKey must be ChunkPos");
			public:
				size_t operator()(const CubA4::mod::world::ChunkPos &chunkPos) const
				{
					constexpr auto axisHashSize = (sizeof(size_t) * 8) /4;
					size_t xKey = chunkPos.x % axisHashSize;
					size_t yKey = chunkPos.y % axisHashSize;
					size_t zKey = chunkPos.z % axisHashSize;
					return zKey << axisHashSize * 2 | yKey << axisHashSize | xKey;
				}
			};

			using ChunkPosHash = ChunkPosHashT<CubA4::mod::world::ChunkPos>;
		}
	}
}

#endif // CHUNKPOSHASH_HPP
