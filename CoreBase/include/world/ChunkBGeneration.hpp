#pragma once

#include <vector>
#include <array>
#include <memory>
#include <limits>
#include <world/Position.hpp>
#include <world/data/BlockData.hpp>
#include <object/IBlock.hpp>
#include <core/IIdentityiMap.hpp>

namespace CubA4::world
{
	struct ChunkBGeneration
	{
		CubA4::world::ChunkPos pos;

		struct BlockInfo
		{
			CubA4::core::IIdentityiMap::IdType blockId = std::numeric_limits<CubA4::core::IIdentityiMap::IdType>::max();
			std::shared_ptr<CubA4::world::BlockData> data;
		};

		struct Fill
		{
			BlockInfo info;
			BlockInChunkPos from;
			BlockInChunkPos to;
		};

		struct Add
		{
			BlockInfo info;
			std::vector<BlockInChunkPos> positions;
		};

		struct Layer
		{
			std::vector<Fill> fill;
			std::vector<Add> add;
		};

		std::vector<Layer> layers;
	};
}