#pragma once

#include <vector>
#include <memory>
#include <world/Position.hpp>
#include <world/BlockData.hpp>
#include <object/IBlock.hpp>

namespace CubA4::world
{
	struct ChunkBModification
	{
		struct AddInfo
		{
			std::shared_ptr<const CubA4::object::IBlock> block;
			CubA4::world::BlockData data;
			CubA4::world::BlockInChunkPos pos;
		};

		/// Can be only applied to unique data
		struct ModifyInfo
		{
			BlockPosition where;
			CubA4::world::BlockData newData;
		};

		struct RemoveInfo
		{
			CubA4::world::BlockInChunkPos pos;
			CubA4::world::Layer layer;
		};
		std::vector<AddInfo> add;
		std::vector<ModifyInfo> mod;
		std::vector<RemoveInfo> remove;
	};
}
